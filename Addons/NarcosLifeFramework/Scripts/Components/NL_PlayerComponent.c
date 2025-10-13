//------------------------------------------------------------------------------------------------
// NarcosLife Player Component
// Component attached to player entities for NarcosLife functionality
//------------------------------------------------------------------------------------------------
class NL_PlayerComponentClass : ScriptComponentClass
{
}

//------------------------------------------------------------------------------------------------
class NL_PlayerComponent : ScriptComponent
{
 protected int m_iPlayerId;
 protected ref NL_PlayerData m_PlayerData;
 
 //------------------------------------------------------------------------------------------------
 override void OnPostInit(IEntity owner)
 {
  super.OnPostInit(owner);
  
  SetEventMask(owner, EntityEvent.INIT);
 }
 
 //------------------------------------------------------------------------------------------------
 override void EOnInit(IEntity owner)
 {
  // Initialize player component
  Print("[NarcosLife] Player Component initialized", LogLevel.NORMAL);
 }
 
 //------------------------------------------------------------------------------------------------
 void SetPlayerId(int playerId)
 {
  m_iPlayerId = playerId;
 }
 
 //------------------------------------------------------------------------------------------------
 int GetPlayerId()
 {
  return m_iPlayerId;
 }
 
 //------------------------------------------------------------------------------------------------
 void SetPlayerData(NL_PlayerData data)
 {
  m_PlayerData = data;
 }
 
 //------------------------------------------------------------------------------------------------
 NL_PlayerData GetPlayerData()
 {
  return m_PlayerData;
 }
 
 //------------------------------------------------------------------------------------------------
 void ShowMoney()
 {
  if (m_PlayerData)
  {
   Print(string.Format("[NarcosLife] Player %1 money: $%2", m_iPlayerId, m_PlayerData.GetMoney()), LogLevel.NORMAL);
  }
 }
 
 //------------------------------------------------------------------------------------------------
 void ShowFaction()
 {
  if (m_PlayerData)
  {
   int factionId = m_PlayerData.GetFactionId();
   if (factionId != -1)
    Print(string.Format("[NarcosLife] Player %1 faction: %2", m_iPlayerId, factionId), LogLevel.NORMAL);
   else
    Print(string.Format("[NarcosLife] Player %1 has no faction", m_iPlayerId), LogLevel.NORMAL);
  }
 }
}
