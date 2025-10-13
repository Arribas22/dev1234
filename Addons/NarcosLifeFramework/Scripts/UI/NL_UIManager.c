//------------------------------------------------------------------------------------------------
// NarcosLife UI Manager
// Manages UI elements for the NarcosLife framework
//------------------------------------------------------------------------------------------------
class NL_UIManager
{
 protected Widget m_wRoot;
 protected TextWidget m_wMoneyDisplay;
 protected TextWidget m_wFactionDisplay;
 protected Widget m_wShopMenu;
 
 //------------------------------------------------------------------------------------------------
 void NL_UIManager()
 {
  Print("[NarcosLife] UI Manager initialized", LogLevel.NORMAL);
 }
 
 //------------------------------------------------------------------------------------------------
 void Initialize()
 {
  // Load UI layout
  // m_wRoot = GetGame().GetWorkspace().CreateWidgets("UI/Layouts/NarcosLife_HUD.layout");
 }
 
 //------------------------------------------------------------------------------------------------
 void UpdateMoneyDisplay(float money)
 {
  if (m_wMoneyDisplay)
  {
   m_wMoneyDisplay.SetText(string.Format("$%1", money.ToString()));
  }
 }
 
 //------------------------------------------------------------------------------------------------
 void UpdateFactionDisplay(string factionName)
 {
  if (m_wFactionDisplay)
  {
   m_wFactionDisplay.SetText(factionName);
  }
 }
 
 //------------------------------------------------------------------------------------------------
 void ShowShopMenu(NL_Shop shop)
 {
  // Display shop menu with items
  Print(string.Format("[NarcosLife] Opening shop: %1", shop.GetName()), LogLevel.NORMAL);
 }
 
 //------------------------------------------------------------------------------------------------
 void HideShopMenu()
 {
  if (m_wShopMenu)
   m_wShopMenu.SetVisible(false);
 }
 
 //------------------------------------------------------------------------------------------------
 void ShowNotification(string message, float duration = 5.0)
 {
  Print(string.Format("[NarcosLife] Notification: %1", message), LogLevel.NORMAL);
 }
}
