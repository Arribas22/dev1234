//------------------------------------------------------------------------------------------------
// NarcosLife Game Mode Base
// Main game mode class for NarcosLife Framework
//------------------------------------------------------------------------------------------------
class NL_GameModeBase : SCR_BaseGameMode
{
 [Attribute("5000", UIWidgets.EditBox, "Starting money for players")]
 protected int m_iStartingMoney;
 
 [Attribute("300", UIWidgets.EditBox, "Salary interval in seconds")]
 protected float m_fSalaryInterval;
 
 [Attribute("500", UIWidgets.EditBox, "Salary amount")]
 protected float m_fSalaryAmount;
 
 protected ref map<int, ref NL_PlayerData> m_mPlayerData;
 protected ref NL_EconomySystem m_EconomySystem;
 protected ref NL_FactionSystem m_FactionSystem;
 protected ref NL_WeaponSystem m_WeaponSystem;
 
 //------------------------------------------------------------------------------------------------
 override void OnInit()
 {
  super.OnInit();
  
  m_mPlayerData = new map<int, ref NL_PlayerData>();
  m_EconomySystem = new NL_EconomySystem();
  m_FactionSystem = new NL_FactionSystem();
  m_WeaponSystem = new NL_WeaponSystem();
  
  Print("[NarcosLife] Game Mode initialized", LogLevel.NORMAL);
 }
 
 //------------------------------------------------------------------------------------------------
 override void OnPlayerConnected(int playerId)
 {
  super.OnPlayerConnected(playerId);
  
  NL_PlayerData playerData = new NL_PlayerData();
  playerData.SetPlayerId(playerId);
  playerData.SetMoney(m_iStartingMoney);
  
  m_mPlayerData.Insert(playerId, playerData);
  
  Print(string.Format("[NarcosLife] Player %1 connected with starting money: %2", playerId, m_iStartingMoney), LogLevel.NORMAL);
 }
 
 //------------------------------------------------------------------------------------------------
 override void OnPlayerDisconnected(int playerId, KickCauseCode cause, int timeout)
 {
  super.OnPlayerDisconnected(playerId, cause, timeout);
  
  if (m_mPlayerData.Contains(playerId))
  {
   m_mPlayerData.Remove(playerId);
   Print(string.Format("[NarcosLife] Player %1 disconnected", playerId), LogLevel.NORMAL);
  }
 }
 
 //------------------------------------------------------------------------------------------------
 NL_PlayerData GetPlayerData(int playerId)
 {
  return m_mPlayerData.Get(playerId);
 }
 
 //------------------------------------------------------------------------------------------------
 NL_EconomySystem GetEconomySystem()
 {
  return m_EconomySystem;
 }
 
 //------------------------------------------------------------------------------------------------
 NL_FactionSystem GetFactionSystem()
 {
  return m_FactionSystem;
 }
 
 //------------------------------------------------------------------------------------------------
 NL_WeaponSystem GetWeaponSystem()
 {
  return m_WeaponSystem;
 }
}
