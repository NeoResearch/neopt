#ifndef MERKLE_TREE_HPP
#define MERKLE_TREE_HPP

// c++ standard part
#include <vector>

// neopt core part
#include <crypto/Crypto.h>
#include <numbers/UInt256.hpp>
#include <system/vhelper.hpp>
#include <system/printable.h>

namespace neopt {
class MerkleTreeNode
{
public:
   UInt256 Hash;
   MerkleTreeNode* Parent;
   MerkleTreeNode* LeftChild;
   MerkleTreeNode* RightChild;

   MerkleTreeNode()
     : LeftChild(nullptr)
     , RightChild(nullptr)
   {
      std::cout << "MerkleTreeNode()" << std::endl;
   }

   MerkleTreeNode(const UInt256& _hash)
     : Hash(_hash)
     , LeftChild(nullptr)
     , RightChild(nullptr)
   {
      std::cout << "MerkleTreeNode(UInt256)" << std::endl;
   }

   bool IsLeaf()
   {
      return LeftChild == nullptr && RightChild == nullptr;
   }

   bool IsRoot()
   {
      return Parent == nullptr;
   }

   string ToString() const
   {
      stringstream ss;
      ss << "MTNode{(this=" << this << "); " << Hash.ToString() << " ; left=" << LeftChild << " right=" << RightChild << "}";
      return ss.str();
   }

   static void PrintMTArray(const std::vector<MerkleTreeNode*>& L)
   {
      stringstream ss;
      ss << "MPTList[";
      for (unsigned i = 0; i < L.size(); i++)
         ss << L[i]->ToString() << "\t";
      ss << "]";
      std::cout << ss.str() << std::endl;
   }
};

class MerkleTree
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

   // TODO: TRIM?

   /*
      public void Trim(BitArray flags)
      {
           flags = new BitArray(flags);
           flags.Length = 1 << (Depth - 1);
           Trim(root, 0, Depth, flags);
      }

      private static void Trim(MerkleTreeNode node, int index, int depth, BitArray flags)
      {
           if (depth == 1) return;
           if (node.LeftChild == null) return; // if left is null, then right must be null
           if (depth == 2)
           {
               if (!flags.Get(index * 2) && !flags.Get(index * 2 + 1))
               {
                   node.LeftChild = null;
                   node.RightChild = null;
               }
           }
           else
           {
               Trim(node.LeftChild, index * 2, depth - 1, flags);
               Trim(node.RightChild, index * 2 + 1, depth - 1, flags);
               if (node.LeftChild.LeftChild == null && node.RightChild.RightChild == null)
               {
                   node.LeftChild = null;
                   node.RightChild = null;
               }
           }
        }
   */
};
}

#endif
