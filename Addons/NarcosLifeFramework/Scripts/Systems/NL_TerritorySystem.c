//------------------------------------------------------------------------------------------------
// NarcosLife Territory System
// Manages territory control, capture points, and territory benefits
//------------------------------------------------------------------------------------------------
class NL_TerritorySystem
{
 protected ref array<ref NL_Territory> m_aTerritories;
 
 //------------------------------------------------------------------------------------------------
 void NL_TerritorySystem()
 {
  m_aTerritories = new array<ref NL_Territory>();
  
  Print("[NarcosLife] Territory System initialized", LogLevel.NORMAL);
 }
 
 //------------------------------------------------------------------------------------------------
 NL_Territory CreateTerritory(string name, vector position, float radius, float income)
 {
  NL_Territory territory = new NL_Territory(name, position, radius, income);
  m_aTerritories.Insert(territory);
  
  Print(string.Format("[NarcosLife] Territory created: %1 at position %2", name, position.ToString()), LogLevel.NORMAL);
  return territory;
 }
 
 //------------------------------------------------------------------------------------------------
 array<ref NL_Territory> GetAllTerritories()
 {
  return m_aTerritories;
 }
 
 //------------------------------------------------------------------------------------------------
 NL_Territory GetTerritoryAtPosition(vector position)
 {
  foreach (NL_Territory territory : m_aTerritories)
  {
   if (vector.Distance(territory.GetPosition(), position) <= territory.GetRadius())
    return territory;
  }
  
  return null;
 }
 
 //------------------------------------------------------------------------------------------------
 void UpdateTerritories(float deltaTime)
 {
  foreach (NL_Territory territory : m_aTerritories)
  {
   territory.Update(deltaTime);
  }
 }
}

//------------------------------------------------------------------------------------------------
// Territory Class
//------------------------------------------------------------------------------------------------
class NL_Territory
{
 protected string m_sName;
 protected vector m_vPosition;
 protected float m_fRadius;
 protected float m_fIncome;
 protected int m_iOwnerFactionId;
 protected float m_fCaptureProgress;
 protected int m_iCapturingFactionId;
 
 //------------------------------------------------------------------------------------------------
 void NL_Territory(string name, vector position, float radius, float income)
 {
  m_sName = name;
  m_vPosition = position;
  m_fRadius = radius;
  m_fIncome = income;
  m_iOwnerFactionId = -1;
  m_fCaptureProgress = 0;
  m_iCapturingFactionId = -1;
 }
 
 //------------------------------------------------------------------------------------------------
 string GetName()
 {
  return m_sName;
 }
 
 //------------------------------------------------------------------------------------------------
 vector GetPosition()
 {
  return m_vPosition;
 }
 
 //------------------------------------------------------------------------------------------------
 float GetRadius()
 {
  return m_fRadius;
 }
 
 //------------------------------------------------------------------------------------------------
 int GetOwnerFactionId()
 {
  return m_iOwnerFactionId;
 }
 
 //------------------------------------------------------------------------------------------------
 void SetOwnerFaction(int factionId)
 {
  m_iOwnerFactionId = factionId;
  m_fCaptureProgress = 0;
  m_iCapturingFactionId = -1;
  
  Print(string.Format("[NarcosLife] Territory %1 captured by faction %2", m_sName, factionId), LogLevel.NORMAL);
 }
 
 //------------------------------------------------------------------------------------------------
 float GetIncome()
 {
  return m_fIncome;
 }
 
 //------------------------------------------------------------------------------------------------
 void StartCapture(int factionId)
 {
  m_iCapturingFactionId = factionId;
  m_fCaptureProgress = 0;
 }
 
 //------------------------------------------------------------------------------------------------
 void UpdateCapture(float deltaTime, int factionId)
 {
  if (m_iCapturingFactionId == factionId)
  {
   m_fCaptureProgress += deltaTime * 0.01; // 1% per second
   
   if (m_fCaptureProgress >= 1.0)
   {
    SetOwnerFaction(factionId);
   }
  }
 }
 
 //------------------------------------------------------------------------------------------------
 void Update(float deltaTime)
 {
  // Territory update logic
 }
}
