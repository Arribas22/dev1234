//------------------------------------------------------------------------------------------------
// NarcosLife Weapon System
// Manages weapons, crafting, durability, and weapon shops
//------------------------------------------------------------------------------------------------
class NL_WeaponSystem
{
 protected ref array<ref NL_WeaponData> m_aWeaponRegistry;
 protected ref map<string, ref NL_WeaponData> m_mWeaponsByName;
 
 //------------------------------------------------------------------------------------------------
 void NL_WeaponSystem()
 {
  m_aWeaponRegistry = new array<ref NL_WeaponData>();
  m_mWeaponsByName = new map<string, ref NL_WeaponData>();
  
  InitializeWeaponRegistry();
  
  Print("[NarcosLife] Weapon System initialized", LogLevel.NORMAL);
 }
 
 //------------------------------------------------------------------------------------------------
 void InitializeWeaponRegistry()
 {
  // Register common weapons used in NarcosLife scenarios
  RegisterWeapon("AK-47", "Prefabs/Weapons/Rifles/AK47.et", 15000, 0.85);
  RegisterWeapon("M4A1", "Prefabs/Weapons/Rifles/M4A1.et", 18000, 0.90);
  RegisterWeapon("Glock 17", "Prefabs/Weapons/Pistols/Glock17.et", 5000, 0.75);
  RegisterWeapon("MP5", "Prefabs/Weapons/SMGs/MP5.et", 12000, 0.80);
  RegisterWeapon("Remington 870", "Prefabs/Weapons/Shotguns/Rem870.et", 8000, 0.70);
  RegisterWeapon("Dragunov SVD", "Prefabs/Weapons/Rifles/SVD.et", 25000, 0.88);
 }
 
 //------------------------------------------------------------------------------------------------
 void RegisterWeapon(string name, string prefabPath, float price, float reliability)
 {
  NL_WeaponData weaponData = new NL_WeaponData(name, prefabPath, price, reliability);
  m_aWeaponRegistry.Insert(weaponData);
  m_mWeaponsByName.Insert(name, weaponData);
  
  Print(string.Format("[NarcosLife] Weapon registered: %1 (Price: %2)", name, price), LogLevel.NORMAL);
 }
 
 //------------------------------------------------------------------------------------------------
 NL_WeaponData GetWeaponData(string weaponName)
 {
  if (m_mWeaponsByName.Contains(weaponName))
   return m_mWeaponsByName.Get(weaponName);
   
  return null;
 }
 
 //------------------------------------------------------------------------------------------------
 array<ref NL_WeaponData> GetAllWeapons()
 {
  return m_aWeaponRegistry;
 }
 
 //------------------------------------------------------------------------------------------------
 bool CanCraftWeapon(NL_PlayerData player, string weaponName)
 {
  NL_WeaponData weaponData = GetWeaponData(weaponName);
  if (!weaponData)
   return false;
   
  return player.GetMoney() >= weaponData.GetCraftingCost();
 }
 
 //------------------------------------------------------------------------------------------------
 NL_WeaponOwnership CraftWeapon(NL_PlayerData player, string weaponName)
 {
  NL_WeaponData weaponData = GetWeaponData(weaponName);
  if (!weaponData || !CanCraftWeapon(player, weaponName))
   return null;
   
  player.RemoveMoney(weaponData.GetCraftingCost());
  
  NL_WeaponOwnership ownership = new NL_WeaponOwnership(weaponName, weaponData.GetReliability());
  player.AddWeapon(ownership);
  
  Print(string.Format("[NarcosLife] Player %1 crafted weapon: %2", player.GetPlayerId(), weaponName), LogLevel.NORMAL);
  return ownership;
 }
 
 //------------------------------------------------------------------------------------------------
 bool PurchaseWeapon(NL_PlayerData player, string weaponName, NL_EconomySystem economy)
 {
  NL_WeaponData weaponData = GetWeaponData(weaponName);
  if (!weaponData)
   return false;
   
  if (!economy.CanAfford(player, weaponData.GetPrice()))
   return false;
   
  if (economy.ProcessTransaction(player, -weaponData.GetPrice(), "Weapon purchase: " + weaponName))
  {
   NL_WeaponOwnership ownership = new NL_WeaponOwnership(weaponName, weaponData.GetReliability());
   player.AddWeapon(ownership);
   
   Print(string.Format("[NarcosLife] Player %1 purchased weapon: %2", player.GetPlayerId(), weaponName), LogLevel.NORMAL);
   return true;
  }
  
  return false;
 }
}

//------------------------------------------------------------------------------------------------
// Weapon Data Class
//------------------------------------------------------------------------------------------------
class NL_WeaponData
{
 protected string m_sWeaponName;
 protected string m_sPrefabPath;
 protected float m_fPrice;
 protected float m_fReliability;
 protected float m_fCraftingCost;
 
 //------------------------------------------------------------------------------------------------
 void NL_WeaponData(string name, string prefabPath, float price, float reliability)
 {
  m_sWeaponName = name;
  m_sPrefabPath = prefabPath;
  m_fPrice = price;
  m_fReliability = reliability;
  m_fCraftingCost = price * 0.7; // Crafting costs 70% of purchase price
 }
 
 //------------------------------------------------------------------------------------------------
 string GetName()
 {
  return m_sWeaponName;
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
 float GetReliability()
 {
  return m_fReliability;
 }
 
 //------------------------------------------------------------------------------------------------
 float GetCraftingCost()
 {
  return m_fCraftingCost;
 }
}

//------------------------------------------------------------------------------------------------
// Weapon Ownership Class
//------------------------------------------------------------------------------------------------
class NL_WeaponOwnership
{
 protected string m_sWeaponName;
 protected float m_fDurability;
 protected int m_iKills;
 protected float m_fTimePurchased;
 
 //------------------------------------------------------------------------------------------------
 void NL_WeaponOwnership(string name, float initialDurability = 1.0)
 {
  m_sWeaponName = name;
  m_fDurability = initialDurability;
  m_iKills = 0;
  m_fTimePurchased = 0; // Should be set to game time
 }
 
 //------------------------------------------------------------------------------------------------
 string GetWeaponName()
 {
  return m_sWeaponName;
 }
 
 //------------------------------------------------------------------------------------------------
 float GetDurability()
 {
  return m_fDurability;
 }
 
 //------------------------------------------------------------------------------------------------
 void DegradeDurability(float amount)
 {
  m_fDurability = Math.Max(0, m_fDurability - amount);
 }
 
 //------------------------------------------------------------------------------------------------
 void AddKill()
 {
  m_iKills++;
 }
 
 //------------------------------------------------------------------------------------------------
 int GetKills()
 {
  return m_iKills;
 }
 
 //------------------------------------------------------------------------------------------------
 bool IsOperational()
 {
  return m_fDurability > 0.1; // Weapon becomes unreliable below 10% durability
 }
}
