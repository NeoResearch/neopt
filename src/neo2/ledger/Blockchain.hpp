#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

// c++ standard part
#include<vector>

// neopt core part
#include<ledger/IBlockchain.hpp>
#include<ledger/NeoSystem.h>

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt
{

class Blockchain : public IBlockchain
{
public:

   // TODO: avoid singleton for now
   /*
   // Singleton Class (TODO: use pattern on inheritance)
   static IBlockchain* _singleton;

   static IBlockchain& Singleton()
   {
      return *_singleton;
   }
   */



   // method to import blocks
   void OnImport(std::vector<Block>& blocks)
   {
      for(unsigned i=0; i<blocks.size(); i++)
      {
         Block block = blocks[i];
         if (block.Index <= Height())
            continue;
         if (block.Index != Height() + 1)
            NEOPT_EXCEPTION("Blockchain::OnImport InvalidOperationException");
            //throw new InvalidOperationException();
         Persist(block);
         SaveHeaderHashList();
      }
       //Sender.Tell(new ImportCompleted()); // no more callbacks.. no akka here
   }


private:

   void SaveHeaderHashList(ISnapshot* snapshot = nullptr)
   {
      /*
      if ((header_index.Count - stored_header_count < 2000))
          return;
      bool snapshot_created = snapshot == null;
      if (snapshot_created) snapshot = GetSnapshot();
      try
      {
          while (header_index.Count - stored_header_count >= 2000)
          {
              snapshot.HeaderHashList.Add(stored_header_count, new HeaderHashList
              {
                  Hashes = header_index.Skip((int)stored_header_count).Take(2000).ToArray()
              });
              stored_header_count += 2000;
          }
          if (snapshot_created) snapshot.Commit();
      }
      finally
      {
          if (snapshot_created) snapshot.Dispose();
      }
      */
   }

   // this method is the heart of the blockchain: TODO
   void Persist(Block& block)
   {
      std::cout << "WELCOME TO THE PERSIST METHOD! THIS IS WHERE MAGIC HAPPENS!" << std::endl;

      /*
        using (Snapshot snapshot = GetSnapshot())
        {
           List<ApplicationExecuted> all_application_executed = new List<ApplicationExecuted>();
           snapshot.PersistingBlock = block;
           snapshot.Blocks.Add(block.Hash, new BlockState
           {
                SystemFeeAmount = snapshot.GetSysFeeAmount(block.PrevHash) + (long)block.Transactions.Sum(p => p.SystemFee),
                TrimmedBlock = block.Trim()
           });
           foreach (Transaction tx in block.Transactions)
           {
                snapshot.Transactions.Add(tx.Hash, new TransactionState
                {
                    BlockIndex = block.Index,
                    Transaction = tx
                });
                snapshot.UnspentCoins.Add(tx.Hash, new UnspentCoinState
                {
                    Items = Enumerable.Repeat(CoinState.Confirmed, tx.Outputs.Length).ToArray()
                });
                foreach (TransactionOutput output in tx.Outputs)
                {
                    AccountState account = snapshot.Accounts.GetAndChange(output.ScriptHash, () => new AccountState(output.ScriptHash));
                    if (account.Balances.ContainsKey(output.AssetId))
                        account.Balances[output.AssetId] += output.Value;
                    else
                        account.Balances[output.AssetId] = output.Value;
                    if (output.AssetId.Equals(GoverningToken.Hash) && account.Votes.Length > 0)
                    {
                        foreach (ECPoint pubkey in account.Votes)
                           snapshot.Validators.GetAndChange(pubkey, () => new ValidatorState(pubkey)).Votes += output.Value;
                        snapshot.ValidatorsCount.GetAndChange().Votes[account.Votes.Length - 1] += output.Value;
                    }
                }
                foreach (var group in tx.Inputs.GroupBy(p => p.PrevHash))
                {
                    TransactionState tx_prev = snapshot.Transactions[group.Key];
                    foreach (CoinReference input in group)
                    {
                        snapshot.UnspentCoins.GetAndChange(input.PrevHash).Items[input.PrevIndex] |= CoinState.Spent;
                        TransactionOutput out_prev = tx_prev.Transaction.Outputs[input.PrevIndex];
                        AccountState account = snapshot.Accounts.GetAndChange(out_prev.ScriptHash);
                        if (out_prev.AssetId.Equals(GoverningToken.Hash))
                        {
                           snapshot.SpentCoins.GetAndChange(input.PrevHash, () => new SpentCoinState
                           {
                                TransactionHash = input.PrevHash,
                                TransactionHeight = tx_prev.BlockIndex,
                                Items = new Dictionary<ushort, uint>()
                           }).Items.Add(input.PrevIndex, block.Index);
                           if (account.Votes.Length > 0)
                           {
                                foreach (ECPoint pubkey in account.Votes)
                                {
                                    ValidatorState validator = snapshot.Validators.GetAndChange(pubkey);
                                    validator.Votes -= out_prev.Value;
                                    if (!validator.Registered && validator.Votes.Equals(Fixed8.Zero))
                                        snapshot.Validators.Delete(pubkey);
                                }
                                snapshot.ValidatorsCount.GetAndChange().Votes[account.Votes.Length - 1] -= out_prev.Value;
                           }
                        }
                        account.Balances[out_prev.AssetId] -= out_prev.Value;
                    }
                }
                List<ApplicationExecutionResult> execution_results = new List<ApplicationExecutionResult>();
                switch (tx)
                {
#pragma warning disable CS0612
                    case RegisterTransaction tx_register:
                        snapshot.Assets.Add(tx.Hash, new AssetState
                        {
                           AssetId = tx_register.Hash,
                           AssetType = tx_register.AssetType,
                           Name = tx_register.Name,
                           Amount = tx_register.Amount,
                           Available = Fixed8.Zero,
                           Precision = tx_register.Precision,
                           Fee = Fixed8.Zero,
                           FeeAddress = new UInt160(),
                           Owner = tx_register.Owner,
                           Admin = tx_register.Admin,
                           Issuer = tx_register.Admin,
                           Expiration = block.Index + 2 * 2000000,
                           IsFrozen = false
                        });
                        break;
#pragma warning restore CS0612
                    case IssueTransaction _:
                        foreach (TransactionResult result in tx.GetTransactionResults().Where(p => p.Amount < Fixed8.Zero))
                           snapshot.Assets.GetAndChange(result.AssetId).Available -= result.Amount;
                        break;
                    case ClaimTransaction _:
                        foreach (CoinReference input in ((ClaimTransaction)tx).Claims)
                        {
                           if (snapshot.SpentCoins.TryGet(input.PrevHash)?.Items.Remove(input.PrevIndex) == true)
                                snapshot.SpentCoins.GetAndChange(input.PrevHash);
                        }
                        break;
#pragma warning disable CS0612
                    case EnrollmentTransaction tx_enrollment:
                        snapshot.Validators.GetAndChange(tx_enrollment.PublicKey, () => new ValidatorState(tx_enrollment.PublicKey)).Registered = true;
                        break;
#pragma warning restore CS0612
                    case StateTransaction tx_state:
                        foreach (StateDescriptor descriptor in tx_state.Descriptors)
                           switch (descriptor.Type)
                           {
                                case StateType.Account:
                                    ProcessAccountStateDescriptor(descriptor, snapshot);
                                    break;
                                case StateType.Validator:
                                    ProcessValidatorStateDescriptor(descriptor, snapshot);
                                    break;
                           }
                        break;
#pragma warning disable CS0612
                    case PublishTransaction tx_publish:
                        snapshot.Contracts.GetOrAdd(tx_publish.ScriptHash, () => new ContractState
                        {
                           Script = tx_publish.Script,
                           ParameterList = tx_publish.ParameterList,
                           ReturnType = tx_publish.ReturnType,
                           ContractProperties = (ContractPropertyState)Convert.ToByte(tx_publish.NeedStorage),
                           Name = tx_publish.Name,
                           CodeVersion = tx_publish.CodeVersion,
                           Author = tx_publish.Author,
                           Email = tx_publish.Email,
                           Description = tx_publish.Description
                        });
                        break;
#pragma warning restore CS0612
                    case InvocationTransaction tx_invocation:
                        using (ApplicationEngine engine = new ApplicationEngine(TriggerType.Application, tx_invocation, snapshot.Clone(), tx_invocation.Gas))
                        {
                           engine.LoadScript(tx_invocation.Script);
                           engine.Execute();
                           if (!engine.State.HasFlag(VMState.FAULT))
                           {
                                engine.Service.Commit();
                           }
                           execution_results.Add(new ApplicationExecutionResult
                           {
                                Trigger = TriggerType.Application,
                                ScriptHash = tx_invocation.Script.ToScriptHash(),
                                VMState = engine.State,
                                GasConsumed = engine.GasConsumed,
                                Stack = engine.ResultStack.ToArray(),
                                Notifications = engine.Service.Notifications.ToArray()
                           });
                        }
                        break;
                }
                if (execution_results.Count > 0)
                {
                    ApplicationExecuted application_executed = new ApplicationExecuted
                    {
                        Transaction = tx,
                        ExecutionResults = execution_results.ToArray()
                    };
                    Context.System.EventStream.Publish(application_executed);
                    all_application_executed.Add(application_executed);
                }
           }
           snapshot.BlockHashIndex.GetAndChange().Hash = block.Hash;
           snapshot.BlockHashIndex.GetAndChange().Index = block.Index;
           if (block.Index == header_index.Count)
           {
                header_index.Add(block.Hash);
                snapshot.HeaderHashIndex.GetAndChange().Hash = block.Hash;
                snapshot.HeaderHashIndex.GetAndChange().Index = block.Index;
           }
           foreach (IPersistencePlugin plugin in Plugin.PersistencePlugins)
                plugin.OnPersist(snapshot, all_application_executed);
           snapshot.Commit();
           List<Exception> commitExceptions = null;
           foreach (IPersistencePlugin plugin in Plugin.PersistencePlugins)
           {
                try
                {
                    plugin.OnCommit(snapshot);
                }
                catch (Exception ex)
                {
                    if (plugin.ShouldThrowExceptionFromCommit(ex))
                    {
                        if (commitExceptions == null)
                           commitExceptions = new List<Exception>();

                        commitExceptions.Add(ex);
                    }
                }
           }
           if (commitExceptions != null) throw new AggregateException(commitExceptions);
        }
        UpdateCurrentSnapshot();
        OnPersistCompleted(block);
        */
     }
     // finished method: Persist(Block block)


};

}

#endif
