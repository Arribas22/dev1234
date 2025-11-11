//------------------------------------------------------------------------------------------------
// NarcosLife Player Data
// Stores player-specific data for the NarcosLife framework
//------------------------------------------------------------------------------------------------
class NL_PlayerData
{
 protected int m_iPlayerId;
 protected float m_fMoney;
 protected int m_iFactionId;
 protected ref array<ref NL_WeaponOwnership> m_aOwnedWeapons;
 protected int m_iKills;
 protected int m_iDeaths;
 protected float m_fPlayTime;
 
 //------------------------------------------------------------------------------------------------
 void NL_PlayerData()
 {
  m_iPlayerId = -1;
  m_fMoney = 0;
  m_iFactionId = -1;
  m_aOwnedWeapons = new array<ref NL_WeaponOwnership>();
  m_iKills = 0;
  m_iDeaths = 0;
  m_fPlayTime = 0;
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
 void SetMoney(float amount)
 {
  m_fMoney = amount;
 }
 
 //------------------------------------------------------------------------------------------------
 float GetMoney()
 {
  return m_fMoney;
 }
 
 //------------------------------------------------------------------------------------------------
 bool AddMoney(float amount)
 {
  if (amount < 0)
   return false;
   
  m_fMoney += amount;
  return true;
 }
 
 //------------------------------------------------------------------------------------------------
 bool RemoveMoney(float amount)
 {
  if (amount < 0 || m_fMoney < amount)
   return false;
   
  m_fMoney -= amount;
  return true;
 }
 
 //------------------------------------------------------------------------------------------------
 void SetFactionId(int factionId)
 {
  m_iFactionId = factionId;
 }
 
 //------------------------------------------------------------------------------------------------
 int GetFactionId()
 {
  return m_iFactionId;
 }
 
 //------------------------------------------------------------------------------------------------
 void AddWeapon(NL_WeaponOwnership weapon)
 {
  m_aOwnedWeapons.Insert(weapon);
 }
 
 //------------------------------------------------------------------------------------------------
 array<ref NL_WeaponOwnership> GetOwnedWeapons()
 {
  return m_aOwnedWeapons;
 }
 
 //------------------------------------------------------------------------------------------------
 void AddKill()
 {
  m_iKills++;
 }
 
 //------------------------------------------------------------------------------------------------
 void AddDeath()
 {
  m_iDeaths++;
 }
 
 //------------------------------------------------------------------------------------------------
 int GetKills()
 {
  return m_iKills;
 }
 
 //------------------------------------------------------------------------------------------------
 int GetDeaths()
 {
  return m_iDeaths;
 }
 
 //------------------------------------------------------------------------------------------------
 void AddPlayTime(float time)
 {
  m_fPlayTime += time;
 }
 
 //------------------------------------------------------------------------------------------------
 float GetPlayTime()
 {
  return m_fPlayTime;
 }
}
