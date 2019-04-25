#ifndef MERKLE_TREE_HPP
#define MERKLE_TREE_HPP

// c++ standard part
#include<vector>

// neopt core part
#include<numbers/UInt256.hpp>
#include<system/vhelper.hpp>
#include<crypto/Crypto.h>

namespace neopt
{
   class MerkleTreeNode
   {
   public:
      UInt256 Hash;
      MerkleTreeNode* Parent;
      MerkleTreeNode* LeftChild;
      MerkleTreeNode* RightChild;

      MerkleTreeNode()
      {
      }

      MerkleTreeNode(UInt256& _hash) :
         Hash(_hash)
      {
      }

      bool IsLeaf()
      {
         return LeftChild == nullptr && RightChild == nullptr;
      }

      bool IsRoot()
      {
         return Parent == nullptr;
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

      MerkleTree(std::vector<UInt256>& hashes)
      {
           if (hashes.size() == 0)
               NEOPT_EXCEPTION("MerkleTree ArgumentException");
           // TODO: create Select pattern
           //this->root = Build(hashes.Select(p => new MerkleTreeNode { Hash = p }).ToArray());
           int depth = 1;
           for (MerkleTreeNode* i = root; i->LeftChild != nullptr; i = i->LeftChild)
               depth++;
           this->_depth = depth;
      }

      static MerkleTreeNode* Build(std::vector<UInt256>& hashes)
      {
         std::vector<MerkleTreeNode*> leaves(hashes.size(), nullptr);
         for(unsigned i=0; i<hashes.size(); i++)
            leaves[i] = new MerkleTreeNode(hashes[i]);
         return Build(leaves);
      }

      static MerkleTreeNode* Build(std::vector<MerkleTreeNode*>& leaves)
      {
           if (leaves.size() == 0)
               NEOPT_EXCEPTION("MerkleTree Build ArgumentException");
           if (leaves.size() == 1)
               return leaves[0];
           vector<MerkleTreeNode*> parents((leaves.size() + 1) / 2);
           for (int i = 0; i < parents.size(); i++)
           {
               parents[i] = new MerkleTreeNode();
               parents[i]->LeftChild = leaves[i * 2];
               leaves[i * 2]->Parent = parents[i];
               if (i * 2 + 1 == leaves.size())
               {
                   parents[i]->RightChild = parents[i]->LeftChild;
               }
               else
               {
                   parents[i]->RightChild = leaves[i * 2 + 1];
                   leaves[i * 2 + 1]->Parent = parents[i];
               }

               //UInt256 newHash(Crypto::Default().Hash256(vhelper::Concat(parents[i]->LeftChild.Hash.ToArray(), parents[i]->RightChild.Hash.ToArray())));
               //parents[i]->Hash = new UInt256(Crypto.Default.Hash256(parents[i].LeftChild.Hash.ToArray().Concat(parents[i].RightChild.Hash.ToArray()).ToArray()));
               parents[i]->Hash = Crypto::Default().Hash256(vhelper::Concat(parents[i]->LeftChild->Hash.ToArray(), parents[i]->RightChild->Hash.ToArray()));
           }
           return Build(parents); //TailCall
      }

      static UInt256 ComputeRoot(std::vector<UInt256>& hashes)
      {
         if (hashes.size() == 0)
            NEOPT_EXCEPTION("MerkleTree ComputeRoot ArgumentException");
         if (hashes.size() == 1)
            return hashes[0];
         MerkleTree tree(hashes);
         return tree.root->Hash;
      }

   private:
      static void DepthFirstSearch(MerkleTreeNode& node, std::vector<UInt256>& hashes)
      {
         if (node.LeftChild == nullptr)
         {
            // if left is null, then right must be null
            hashes.push_back(node.Hash);
         }
         else
         {
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
