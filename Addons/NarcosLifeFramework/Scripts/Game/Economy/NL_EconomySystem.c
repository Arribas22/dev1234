//------------------------------------------------------------------------------------------------
// NarcosLife Economy System
// Manages the economy, currency, shops, and transactions
//------------------------------------------------------------------------------------------------
class NL_EconomySystem
{
 protected ref array<ref NL_Shop> m_aShops;
 protected float m_fSalaryInterval;
 protected float m_fSalaryAmount;
 protected ref map<int, float> m_mPlayerLastSalary;
 
 //------------------------------------------------------------------------------------------------
 void NL_EconomySystem()
 {
  m_aShops = new array<ref NL_Shop>();
  m_mPlayerLastSalary = new map<int, float>();
  m_fSalaryInterval = 300; // 5 minutes default
  m_fSalaryAmount = 500;
  
  Print("[NarcosLife] Economy System initialized", LogLevel.NORMAL);
 }
 
 //------------------------------------------------------------------------------------------------
 void RegisterShop(NL_Shop shop)
 {
  m_aShops.Insert(shop);
 }
 
 //------------------------------------------------------------------------------------------------
 array<ref NL_Shop> GetShops()
 {
  return m_aShops;
 }
 
 //------------------------------------------------------------------------------------------------
 bool ProcessTransaction(NL_PlayerData player, float amount, string reason)
 {
  if (amount < 0 && !player.RemoveMoney(Math.AbsFloat(amount)))
  {
   Print(string.Format("[NarcosLife] Transaction failed for player %1: insufficient funds", player.GetPlayerId()), LogLevel.WARNING);
   return false;
  }
  
  if (amount > 0)
   player.AddMoney(amount);
  
  Print(string.Format("[NarcosLife] Transaction completed for player %1: %2 (reason: %3)", player.GetPlayerId(), amount, reason), LogLevel.NORMAL);
  return true;
 }
 
 //------------------------------------------------------------------------------------------------
 bool CanAfford(NL_PlayerData player, float price)
 {
  return player.GetMoney() >= price;
 }
 
 //------------------------------------------------------------------------------------------------
 void ProcessSalaries(array<ref NL_PlayerData> players, float currentTime)
 {
  foreach (NL_PlayerData player : players)
  {
   int playerId = player.GetPlayerId();
   float lastSalary = 0;
   
   if (m_mPlayerLastSalary.Contains(playerId))
    lastSalary = m_mPlayerLastSalary.Get(playerId);
   
   if (currentTime - lastSalary >= m_fSalaryInterval)
   {
    player.AddMoney(m_fSalaryAmount);
    m_mPlayerLastSalary.Set(playerId, currentTime);
    Print(string.Format("[NarcosLife] Salary paid to player %1: %2", playerId, m_fSalaryAmount), LogLevel.NORMAL);
   }
  }
 }
}

//------------------------------------------------------------------------------------------------
// Shop Class
//------------------------------------------------------------------------------------------------
class NL_Shop
{
 protected string m_sShopName;
 protected vector m_vPosition;
 protected ref array<ref NL_ShopItem> m_aItems;
 
 //------------------------------------------------------------------------------------------------
 void NL_Shop(string name, vector position)
 {
  m_sShopName = name;
  m_vPosition = position;
  m_aItems = new array<ref NL_ShopItem>();
 }
 
 //------------------------------------------------------------------------------------------------
 void AddItem(NL_ShopItem item)
 {
  m_aItems.Insert(item);
 }
 
 //------------------------------------------------------------------------------------------------
 array<ref NL_ShopItem> GetItems()
 {
  return m_aItems;
 }
 
 //------------------------------------------------------------------------------------------------
 string GetName()
 {
  return m_sShopName;
 }
 
 //------------------------------------------------------------------------------------------------
 vector GetPosition()
 {
  return m_vPosition;
 }
}

//------------------------------------------------------------------------------------------------
// Shop Item Class
//------------------------------------------------------------------------------------------------
class NL_ShopItem
{
 protected string m_sItemName;
 protected string m_sPrefabPath;
 protected float m_fPrice;
 protected int m_iStock;
 
 //------------------------------------------------------------------------------------------------
 void NL_ShopItem(string name, string prefabPath, float price, int stock = -1)
 {
  m_sItemName = name;
  m_sPrefabPath = prefabPath;
  m_fPrice = price;
  m_iStock = stock; // -1 = unlimited
 }
 
 //------------------------------------------------------------------------------------------------
 string GetName()
 {
  return m_sItemName;
 }
 
 //------------------------------------------------------------------------------------------------
 string GetPrefabPath()
 {
  return m_sPrefabPath;
 }
 
 //------------------------------------------------------------------------------------------------
 float GetPrice()
 {
  return m_fPrice;
 }
 
 //------------------------------------------------------------------------------------------------
 int GetStock()
 {
  return m_iStock;
 }
 
 //------------------------------------------------------------------------------------------------
 bool Purchase()
 {
  if (m_iStock == 0)
   return false;
   
  if (m_iStock > 0)
   m_iStock--;
   
  return true;
 }
}
