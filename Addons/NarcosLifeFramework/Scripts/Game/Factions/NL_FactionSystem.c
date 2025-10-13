//------------------------------------------------------------------------------------------------
// NarcosLife Faction System
// Manages factions, territories, and faction warfare
//------------------------------------------------------------------------------------------------
class NL_FactionSystem
{
 protected ref array<ref NL_Faction> m_aFactions;
 protected ref map<int, int> m_mPlayerFactions; // playerId -> factionId
 
 //------------------------------------------------------------------------------------------------
 void NL_FactionSystem()
 {
  m_aFactions = new array<ref NL_Faction>();
  m_mPlayerFactions = new map<int, int>();
  
  // Initialize default factions
  InitializeDefaultFactions();
  
  Print("[NarcosLife] Faction System initialized", LogLevel.NORMAL);
 }
 
 //------------------------------------------------------------------------------------------------
 void InitializeDefaultFactions()
 {
  // Create default factions for NarcosLife gameplay
  CreateFaction("Los Carteles", "Cartel drug trafficking organization", "0 1 0");
  CreateFaction("Policia Nacional", "National Police Force", "0 0 1");
  CreateFaction("FARC", "Revolutionary Armed Forces", "1 0 0");
  CreateFaction("Civiles", "Civilian population", "1 1 1");
 }
 
 //------------------------------------------------------------------------------------------------
 NL_Faction CreateFaction(string name, string description, string color)
 {
  NL_Faction faction = new NL_Faction(m_aFactions.Count(), name, description, color);
  m_aFactions.Insert(faction);
  Print(string.Format("[NarcosLife] Faction created: %1 (ID: %2)", name, faction.GetId()), LogLevel.NORMAL);
  return faction;
 }
 
 //------------------------------------------------------------------------------------------------
 bool AssignPlayerToFaction(int playerId, int factionId)
 {
  if (factionId < 0 || factionId >= m_aFactions.Count())
   return false;
   
  m_mPlayerFactions.Set(playerId, factionId);
  m_aFactions[factionId].AddMember(playerId);
  
  Print(string.Format("[NarcosLife] Player %1 assigned to faction %2", playerId, factionId), LogLevel.NORMAL);
  return true;
 }
 
 //------------------------------------------------------------------------------------------------
 int GetPlayerFaction(int playerId)
 {
  if (m_mPlayerFactions.Contains(playerId))
   return m_mPlayerFactions.Get(playerId);
   
  return -1;
 }
 
 //------------------------------------------------------------------------------------------------
 NL_Faction GetFaction(int factionId)
 {
  if (factionId >= 0 && factionId < m_aFactions.Count())
   return m_aFactions[factionId];
   
  return null;
 }
 
 //------------------------------------------------------------------------------------------------
 array<ref NL_Faction> GetAllFactions()
 {
  return m_aFactions;
 }
 
 //------------------------------------------------------------------------------------------------
 bool AreAllies(int playerId1, int playerId2)
 {
  int faction1 = GetPlayerFaction(playerId1);
  int faction2 = GetPlayerFaction(playerId2);
  
  if (faction1 == -1 || faction2 == -1)
   return false;
   
  return faction1 == faction2 || m_aFactions[faction1].IsAllyWith(faction2);
 }
 
 //------------------------------------------------------------------------------------------------
 bool AreEnemies(int playerId1, int playerId2)
 {
  int faction1 = GetPlayerFaction(playerId1);
  int faction2 = GetPlayerFaction(playerId2);
  
  if (faction1 == -1 || faction2 == -1)
   return false;
   
  return m_aFactions[faction1].IsEnemyWith(faction2);
 }
}

//------------------------------------------------------------------------------------------------
// Faction Class
//------------------------------------------------------------------------------------------------
class NL_Faction
{
 protected int m_iFactionId;
 protected string m_sFactionName;
 protected string m_sDescription;
 protected string m_sColor;
 protected ref array<int> m_aMembers;
 protected ref array<int> m_aAllies;
 protected ref array<int> m_aEnemies;
 protected float m_fFactionMoney;
 protected ref array<vector> m_aTerritories;
 
 //------------------------------------------------------------------------------------------------
 void NL_Faction(int id, string name, string description, string color)
 {
  m_iFactionId = id;
  m_sFactionName = name;
  m_sDescription = description;
  m_sColor = color;
  m_aMembers = new array<int>();
  m_aAllies = new array<int>();
  m_aEnemies = new array<int>();
  m_aTerritories = new array<vector>();
  m_fFactionMoney = 0;
 }
 
 //------------------------------------------------------------------------------------------------
 int GetId()
 {
  return m_iFactionId;
 }
 
 //------------------------------------------------------------------------------------------------
 string GetName()
 {
  return m_sFactionName;
 }
 
 //------------------------------------------------------------------------------------------------
 string GetDescription()
 {
  return m_sDescription;
 }
 
 //------------------------------------------------------------------------------------------------
 void AddMember(int playerId)
 {
  if (!m_aMembers.Contains(playerId))
   m_aMembers.Insert(playerId);
 }
 
 //------------------------------------------------------------------------------------------------
 void RemoveMember(int playerId)
 {
  int index = m_aMembers.Find(playerId);
  if (index != -1)
   m_aMembers.Remove(index);
 }
 
 //------------------------------------------------------------------------------------------------
 array<int> GetMembers()
 {
  return m_aMembers;
 }
 
 //------------------------------------------------------------------------------------------------
 void AddAlly(int factionId)
 {
  if (!m_aAllies.Contains(factionId))
   m_aAllies.Insert(factionId);
 }
 
 //------------------------------------------------------------------------------------------------
 void AddEnemy(int factionId)
 {
  if (!m_aEnemies.Contains(factionId))
   m_aEnemies.Insert(factionId);
 }
 
 //------------------------------------------------------------------------------------------------
 bool IsAllyWith(int factionId)
 {
  return m_aAllies.Contains(factionId);
 }
 
 //------------------------------------------------------------------------------------------------
 bool IsEnemyWith(int factionId)
 {
  return m_aEnemies.Contains(factionId);
 }
 
 //------------------------------------------------------------------------------------------------
 void AddTerritory(vector position)
 {
  m_aTerritories.Insert(position);
 }
 
 //------------------------------------------------------------------------------------------------
 array<vector> GetTerritories()
 {
  return m_aTerritories;
 }
 
 //------------------------------------------------------------------------------------------------
 void AddMoney(float amount)
 {
  m_fFactionMoney += amount;
 }
 
 //------------------------------------------------------------------------------------------------
 float GetMoney()
 {
  return m_fFactionMoney;
 }
}
