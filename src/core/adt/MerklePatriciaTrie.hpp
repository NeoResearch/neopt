#ifndef MERKLE_PATRICIA_TRIE_HPP
#define MERKLE_PATRICIA_TRIE_HPP

// c++ standard part
#include <vector>

// neopt core part
#include <crypto/Crypto.h>
#include <numbers/UInt256.hpp>
#include <system/printable.h>
#include <system/vhelper.hpp>

using namespace std; // TODO: remove

namespace neopt {

/*
// used for encoding and node types
enum MPTType
{
   MPT_NULL = 0x08,
   MPT_branch = 0x10,
   MPT_leaf = 0x20,
   MPT_extension = 0x20
};
*/

class MPTNode : public ISerializable
{
private:
   //MPTType type;
   std::vector<vbyte> contents;
   std::function<vbyte(const vbyte&)> fhash;
   // = [](const UInt256& p) -> MerkleTreeNode* { return new MerkleTreeNode(p); };
   // Crypto::Default().Hash256(this->ToArray());
   //this->root = Build(hashes.Select(p => new MerkleTreeNode { Hash = p }).ToArray());
   //   this->root = Build(vhelper::Select(hashes, sel));

   //= [](const UInt256& p) -> MerkleTreeNode* { return new MerkleTreeNode(p); };

   // IsBranch flag
   // if size==2, must know if it's compact branch or path node (leaf/extension)
   bool branch;

public:
   vbyte hash; // usually UInt256 size, but may not be that...

   // empty node
   MPTNode(std::function<vbyte(const vbyte&)> _fhash)
     : fhash{ _fhash }
   {
      hash = fhash(this->ToArray());
   }

   // general constructor
   MPTNode(const std::vector<vbyte>& _contents, std::function<vbyte(const vbyte&)> _fhash)
     : contents(_contents)
     , fhash{ _fhash }
   {
      hash = fhash(this->ToArray());
   }

   // leaf / extension node
   MPTNode(vbyte encodedPath, vbyte value, std::function<vbyte(const vbyte&)> _fhash)
     : contents(2)
     , fhash{ _fhash }
   {
      //if (encodedPath)
      hash = fhash(this->ToArray());
   }

   virtual void Deserialize(IBinaryReader& reader)
   {
      NEOPT_EXCEPTION("MPT Node Deserialize! Not implemented");
   }

   // compressed branch serialization technique
   virtual void Serialize(IBinaryWriter& writer) const
   {
      if (IsNullNode()) // null node
      {
         // pushes 0x00
         writer.Write((byte)0x00);
      } else if (IsHashNode()) // hash node
      {
         // pushes 0x01
         writer.Write((byte)0x01);

         // must insert all (32) bytes from hash (no prefix needed)
         writer.Write(contents[0]);
      } else if (IsPathNode()) // path node (extension or leaf)
      {
         // pushes 0x02
         writer.Write((byte)0x02);
         // write encoded path as var bytes
         writer.WriteVarBytes(contents[0]);
         if(IsLeaf())
            writer.WriteVarBytes(contents[1]); // key as var bytes
         bytes.insert(bytes.end(), contents[0].begin(), contents[0].end());
      } else if (IsBranchNode()) // branch node
      {
         // pushes size + 1
         // 2: 0x03  ...  17: 0x12
         writer.Write((byte)contents.size() + 1);

         // write all elements
         if (IsFullBranchNode()) {
            for (unsigned i = 0; i < contents.size() - 1; i++)
               writer.Write(contents[i]);       // already serialized
            writer.WriteVarBytes(contents[16]); // var bytes for key
         } else
            for (unsigned i = 0; i < contents.size(); i++)
               writer.Write(contents[i]); // already serialized
      } else {
         NEOPT_EXCEPTION("Unknown MPT Node Serialize! Not implemented");
      }
   }

   // null node (just empty)
   bool IsNullNode() const
   {
      return contents.size() == 0;
   }

   // hash node: single element is a hash ("pointer" to another node)
   bool IsHashNode() const
   {
      return contents.size() == 1;
   }

   // path node: leaf or extension
   bool IsPathNode() const
   {
      return (contents.size() == 2) && !this->branch;
   }

   vnibble GetPath() const
   {
      return vnibble();
   }

   // path node: leaf
   bool IsLeaf() const
   {
      if (!IsPathNode())
         return false;
      bool isLeaf;
      CompactDecode(contents[0], isLeaf);
      return isLeaf;
   }

   // path node: extension
   bool IsExtension() const
   {
      return IsPathNode() && !IsLeaf();
   }

   // branch node: 2 to 17 elements
   bool IsBranchNode() const
   {
      // uses branch node flag
      return (contents.size() >= 2) && (contents.size() <= 17) && this->branch;
   }

   // full branch node: includes all alphabet and a leaf
   bool IsFullBranchNode() const
   {
      return IsBranchNode() && (contents.size() == 17);
   }

   string ToString() const
   {
      stringstream ss;
      ss << "MPTNode{(this=" << this << "); hash=" << hash; //<< " ; type=" << getType() << ";";
      //if (type == 0)
      //   ss << "NULL";
      ss << "}";
      return ss.str();
   }

   // compact encode vector of nibbles. if term = true, it means that node is a leaf
   static vbyte CompactEncode(const vnibble nibbles, bool term = false)
   {
      std::cout << "Encode leaf=" << term << std::endl;
      vnibble v(nibbles);
      bool oddlen = v.size() % 2 == 1; // is odd ?
      nibble flag = 2 * term + oddlen; // 0, 1, 2 or 3
      if (oddlen)                      // odd (just insert flag)
         v.insert(v.begin(), flag);
      else // even (padd with extra zero)
      {
         vnibble adding = { flag, 0X0 };
         v.insert(v.begin(), adding.begin(), adding.end());
      }

      return vhelper::NibblesToBytes(v);
   }

   static vnibble CompactDecode(const vbyte bytes, bool& isLeaf)
   {
      vnibble v = vhelper::BytesToNibbles(bytes);
      bool oddlen = v[0] % 2 == 1;
      isLeaf = v[0] / 2 == 1;
      std::cout << "isLeaf = " << isLeaf << std::endl;
      std::cout << "oddlen = " << oddlen << std::endl;
      if (oddlen)
         v.erase(v.begin(), v.begin() + 1);
      else
         v.erase(v.begin(), v.begin() + 2);
      return v;
   }

   static void PrintMPTNodes(const std::vector<MPTNode*>& L)
   {
      stringstream ss;
      ss << "MPTNodes[";
      for (unsigned i = 0; i < L.size(); i++)
         ss << L[i]->ToString() << "\t";
      ss << "]";
      std::cout << ss.str() << std::endl;
   }
};
}

#endif
