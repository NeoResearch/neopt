#ifndef MERKLE_PATRICIA_TRIE_HPP
#define MERKLE_PATRICIA_TRIE_HPP

// c++ standard part
#include <vector>

// neopt core part
#include <crypto/Crypto.h>
#include <numbers/UInt256.hpp>
#include <system/vhelper.hpp>
#include <system/printable.h>

using namespace std; // TODO: remove

namespace neopt {

// used for encoding and node types
enum MPTType
{
   MPT_NULL = 0x08,
   MPT_branch = 0x10,
   MPT_leaf = 0x20,
   MPT_extension = 0x20
};

class MPTNode
{
   private:
   MPTType type;
   std::vector<vbyte> contents;
   std::function<vbyte(const vbyte&)> fhash;
   // = [](const UInt256& p) -> MerkleTreeNode* { return new MerkleTreeNode(p); };
   // Crypto::Default().Hash256(this->ToArray());
      //this->root = Build(hashes.Select(p => new MerkleTreeNode { Hash = p }).ToArray());
   //   this->root = Build(vhelper::Select(hashes, sel));
      
   //= [](const UInt256& p) -> MerkleTreeNode* { return new MerkleTreeNode(p); };

public:
   vbyte hash; // usually UInt256 size, but may not be that...

   // general constructor
   MPTNode(MPTType _type, const std::vector<vbyte>& _contents, std::function<vbyte(const vbyte&)> _fhash) :
      type{_type}, contents(_contents), fhash{_fhash}
   {
      hash = fhash(this->ToArray());
   }

   // NULL node
   MPTNode(std::function<vbyte(const vbyte&)> _fhash) :
      type{MPT_NULL}, fhash{_fhash}
   {
      hash = fhash(this->ToArray());
   }

   // branch node
   MPTNode(vector<vbyte> branches, vbyte value, std::function<vbyte(const vbyte&)> _fhash) :
      type{MPT_branch}, fhash{_fhash}
   {
      hash = fhash(this->ToArray());
   }

   // leaf node
   MPTNode(vbyte encodedPath, vbyte value, std::function<vbyte(const vbyte&)> _fhash) :
      type{MPT_leaf}, fhash{_fhash}
   {
      hash = fhash(this->ToArray());
   }

   // extension node
   MPTNode(vbyte encodedPath, UInt256 key, std::function<vbyte(const vbyte&)> _fhash) :
      type{MPT_extension}, fhash{_fhash}
   {
      hash = fhash(this->ToArray());
   }

   int getType() const
   { 
      return type;
   }

   vbyte ToArray() const
   {
      if(type == 0)
      {
      // NULL node (count is zero)
      return std::move(vbyte(1, 0x00));
      }

      return std::move(vbyte(0)); // unknown (empty node)
   }

   string ToString() const
   {
      stringstream ss;
      ss << "MPTNode{(this=" << this << "); hash=" << hash << " ; type=" << getType() << ";";
      if(type==0)
         ss << "NULL";
      ss << "}";
      return ss.str();
   }

   // compact encode vector of nibbles. if term = true, it means that node is a leaf
   static vbyte CompactEncode(const vnibble nibbles, bool term = false)
   {
      vnibble v(nibbles);
      bool oddlen = v.size() % 2 == 1; // is odd ?
      nibble flag = 2 * term + oddlen; // 0, 1, 2 or 3
      if(oddlen) // odd (just insert flag)
        v.insert(v.begin(), flag);
      else // even (padd with extra zero)
      {
         vnibble adding = {flag, 0X0};
        v.insert(v.begin(),adding.begin(), adding.end());
      }
    
      return vhelper::NibblesToBytes(v);
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

/*
class MerklePatriciaTrie
{
private:
   MerkleTreeNode* root;
   int _depth;

public:
   int Depth()
   {
      return _depth;
   }

   MerkleTree(const std::vector<UInt256>& hashes)
   {
      std::cout << "MerkleTree(hashes=" << hashes.size() << "): [";
      for (unsigned i = 0; i < hashes.size(); i++)
         std::cout << hashes[i].ToString() << ";";
      std::cout << "]" << std::endl;

      if (hashes.size() == 0)
         NEOPT_EXCEPTION("MerkleTree ArgumentException");
      // TODO: create Select pattern

      std::function<MerkleTreeNode*(const UInt256&)> sel = [](const UInt256& p) -> MerkleTreeNode* { return new MerkleTreeNode(p); };
      //this->root = Build(hashes.Select(p => new MerkleTreeNode { Hash = p }).ToArray());
      this->root = Build(vhelper::Select(hashes, sel));
      int depth = 1;
      for (MerkleTreeNode* i = root; i->LeftChild != nullptr; i = i->LeftChild)
         depth++;
      this->_depth = depth;
   }

   static MerkleTreeNode* Build(const std::vector<UInt256>& hashes)
   {
      std::vector<MerkleTreeNode*> leaves(hashes.size(), nullptr);
      for (unsigned i = 0; i < hashes.size(); i++)
         leaves[i] = new MerkleTreeNode(hashes[i]);
      return Build(leaves);
   }

   static MerkleTreeNode* Build(const std::vector<MerkleTreeNode*>& leaves)
   {
      std::cout << "Build with MerkleTreeNodes: " << leaves.size() << std::endl;
      MerkleTreeNode::PrintMTArray(leaves);
      if (leaves.size() == 0)
         NEOPT_EXCEPTION("MerkleTree Build ArgumentException");
      if (leaves.size() == 1)
         return leaves[0];
      vector<MerkleTreeNode*> parents((leaves.size() + 1) / 2);
      for (int i = 0; i < parents.size(); i++) {
         parents[i] = new MerkleTreeNode();
         parents[i]->LeftChild = leaves[i * 2];
         leaves[i * 2]->Parent = parents[i];
         if (i * 2 + 1 == leaves.size()) {
            parents[i]->RightChild = parents[i]->LeftChild;
         } else {
            parents[i]->RightChild = leaves[i * 2 + 1];
            leaves[i * 2 + 1]->Parent = parents[i];
         }

         //UInt256 newHash(Crypto::Default().Hash256(vhelper::Concat(parents[i]->LeftChild.Hash.ToArray(), parents[i]->RightChild.Hash.ToArray())));
         //parents[i]->Hash = new UInt256(Crypto.Default.Hash256(parents[i].LeftChild.Hash.ToArray().Concat(parents[i].RightChild.Hash.ToArray()).ToArray()));
         //vbyte cat = vhelper::Concat(vhelper::Reverse(parents[i]->LeftChild->Hash.ToArray()), vhelper::Reverse(parents[i]->RightChild->Hash.ToArray()));

         std::cout << "left:\t" << parents[i]->LeftChild->Hash.ToArray() << std::endl;
         std::cout << "right:\t" << parents[i]->RightChild->Hash.ToArray() << std::endl;
         vbyte cat = vhelper::Concat(parents[i]->LeftChild->Hash.ToArray(), parents[i]->RightChild->Hash.ToArray());
         std::cout << "cat:" << cat << std::endl;
         vbyte h = Crypto::Default().Hash256(cat);
         std::cout << "h:" << h << std::endl;
         parents[i]->Hash = UInt256(h);
         std::cout << "NEW HASH=" << parents[i]->Hash.ToString() << std::endl;
      }
      return Build(parents); //TailCall
   }

   static UInt256 ComputeRoot(const std::vector<UInt256>& hashes)
   {
      std::cout << "will compute merkle root" << std::endl;
      if (hashes.size() == 0)
         NEOPT_EXCEPTION("MerkleTree ComputeRoot ArgumentException");
      if (hashes.size() == 1)
         return hashes[0];
      std::cout << "MERKLE BUILD: SIZE IS " << hashes.size() << std::endl;
      MerkleTree tree(hashes);
      std::cout << "MERKLE INITIALIZED" << std::endl;

      return tree.root->Hash;
   }

private:
   static void DepthFirstSearch(MerkleTreeNode& node, std::vector<UInt256>& hashes)
   {
      if (node.LeftChild == nullptr) {
         // if left is null, then right must be null
         hashes.push_back(node.Hash);
      } else {
         // TODO: test this
         DepthFirstSearch(*node.LeftChild, hashes);
         DepthFirstSearch(*node.RightChild, hashes);
      }
   }

public:
   // depth-first order
   std::vector<UInt256> ToHashArray()
   {
      std::vector<UInt256> hashes;
      DepthFirstSearch(*root, hashes);
      return hashes;
   }

};
*/

}

#endif
