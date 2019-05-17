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

   vbyte ToArray() const
   {
      //if (type == 0) {
      // NULL node (count is zero)
      //   return std::move(vbyte(1, 0x00));
      //}

      if(contents.size() == 0) // null node
         return std::move(vbyte(1, 0x00));

      return std::move(vbyte(0)); // unknown (empty node)
   }

   virtual void Deserialize(IBinaryReader& reader)
   {
      
   }

   virtual void Serialize(IBinaryWriter& writer) const
   {

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
      std::cout <<"Encode leaf=" << term << std::endl;
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
