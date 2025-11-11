# Referencia API - NarcosLife Framework

## Índice
- [Game Mode](#game-mode)
- [Player Data](#player-data)
- [Economy System](#economy-system)
- [Faction System](#faction-system)
- [Weapon System](#weapon-system)
- [Territory System](#territory-system)

---

## Game Mode

### NL_GameModeBase

Clase base del modo de juego que gestiona todos los sistemas del framework.

#### Atributos

```c
[Attribute("5000", UIWidgets.EditBox, "Starting money for players")]
protected int m_iStartingMoney;

[Attribute("300", UIWidgets.EditBox, "Salary interval in seconds")]
protected float m_fSalaryInterval;

[Attribute("500", UIWidgets.EditBox, "Salary amount")]
protected float m_fSalaryAmount;
```

#### Métodos Públicos

**GetPlayerData(int playerId) : NL_PlayerData**
```c
// Obtiene los datos de un jugador específico
NL_PlayerData playerData = gameMode.GetPlayerData(playerId);
```

**GetEconomySystem() : NL_EconomySystem**
```c
// Accede al sistema económico
NL_EconomySystem economy = gameMode.GetEconomySystem();
```

**GetFactionSystem() : NL_FactionSystem**
```c
// Accede al sistema de facciones
NL_FactionSystem factions = gameMode.GetFactionSystem();
```

**GetWeaponSystem() : NL_WeaponSystem**
```c
// Accede al sistema de armas
NL_WeaponSystem weapons = gameMode.GetWeaponSystem();
```

---

## Player Data

### NL_PlayerData

Almacena datos específicos de cada jugador.

#### Métodos

**SetMoney(float amount) : void**
```c
playerData.SetMoney(10000); // Establece dinero a $10,000
```

**GetMoney() : float**
```c
float money = playerData.GetMoney();
```

**AddMoney(float amount) : bool**
```c
if (playerData.AddMoney(500)) {
    Print("Dinero añadido exitosamente");
}
```

**RemoveMoney(float amount) : bool**
```c
if (playerData.RemoveMoney(1000)) {
    Print("Compra realizada");
} else {
    Print("Fondos insuficientes");
}
```

**SetFactionId(int factionId) : void**
```c
playerData.SetFactionId(0); // Asigna al jugador a facción 0
```

**GetFactionId() : int**
```c
int factionId = playerData.GetFactionId();
```

**AddWeapon(NL_WeaponOwnership weapon) : void**
```c
NL_WeaponOwnership weapon = new NL_WeaponOwnership("AK-47", 1.0);
playerData.AddWeapon(weapon);
```

**GetOwnedWeapons() : array<ref NL_WeaponOwnership>**
```c
array<ref NL_WeaponOwnership> weapons = playerData.GetOwnedWeapons();
foreach (NL_WeaponOwnership weapon : weapons) {
    Print(weapon.GetWeaponName());
}
```

**AddKill() : void / GetKills() : int**
```c
playerData.AddKill();
int kills = playerData.GetKills();
```

**AddDeath() : void / GetDeaths() : int**
```c
playerData.AddDeath();
int deaths = playerData.GetDeaths();
```

---

## Economy System

### NL_EconomySystem

Gestiona la economía del servidor.

#### Métodos

**RegisterShop(NL_Shop shop) : void**
```c
NL_Shop shop = new NL_Shop("Armeria", "5000 50 5000");
economy.RegisterShop(shop);
```

**ProcessTransaction(NL_PlayerData player, float amount, string reason) : bool**
```c
if (economy.ProcessTransaction(player, -1000, "Compra de arma")) {
    Print("Transacción exitosa");
}
```

**CanAfford(NL_PlayerData player, float price) : bool**
```c
if (economy.CanAfford(player, 5000)) {
    Print("El jugador puede pagar");
}
```

**ProcessSalaries(array<ref NL_PlayerData> players, float currentTime) : void**
```c
economy.ProcessSalaries(allPlayers, GetGame().GetWorld().GetWorldTime());
```

### NL_Shop

**Constructor:**
```c
NL_Shop(string name, vector position)
```

**Métodos:**
```c
void AddItem(NL_ShopItem item);
array<ref NL_ShopItem> GetItems();
string GetName();
vector GetPosition();
```

**Ejemplo:**
```c
NL_Shop weaponShop = new NL_Shop("Armeria Central", "5000 50 5000");
weaponShop.AddItem(new NL_ShopItem("AK-47", "Prefabs/AK47.et", 15000, -1));
```

### NL_ShopItem

**Constructor:**
```c
NL_ShopItem(string name, string prefabPath, float price, int stock = -1)
```

**Métodos:**
```c
string GetName();
string GetPrefabPath();
float GetPrice();
int GetStock();
bool Purchase(); // Reduce stock en 1
```

---

## Faction System

### NL_FactionSystem

Gestiona facciones y sus relaciones.

#### Métodos

**CreateFaction(string name, string description, string color) : NL_Faction**
```c
NL_Faction newFaction = factionSystem.CreateFaction(
    "Mi Faccion",
    "Descripcion de la faccion",
    "1 0 0"  // Color RGB
);
```

**AssignPlayerToFaction(int playerId, int factionId) : bool**
```c
if (factionSystem.AssignPlayerToFaction(playerId, 0)) {
    Print("Jugador asignado a facción");
}
```

**GetPlayerFaction(int playerId) : int**
```c
int factionId = factionSystem.GetPlayerFaction(playerId);
```

**GetFaction(int factionId) : NL_Faction**
```c
NL_Faction faction = factionSystem.GetFaction(0);
Print(faction.GetName());
```

**AreAllies(int playerId1, int playerId2) : bool**
```c
if (factionSystem.AreAllies(player1Id, player2Id)) {
    Print("Los jugadores son aliados");
}
```

**AreEnemies(int playerId1, int playerId2) : bool**
```c
if (factionSystem.AreEnemies(player1Id, player2Id)) {
    Print("Los jugadores son enemigos");
}
```

### NL_Faction

**Métodos principales:**
```c
int GetId();
string GetName();
string GetDescription();
void AddMember(int playerId);
void RemoveMember(int playerId);
array<int> GetMembers();
void AddAlly(int factionId);
void AddEnemy(int factionId);
bool IsAllyWith(int factionId);
bool IsEnemyWith(int factionId);
void AddTerritory(vector position);
array<vector> GetTerritories();
void AddMoney(float amount);
float GetMoney();
```

---

## Weapon System

### NL_WeaponSystem

Gestiona armas, compras y crafteo.

#### Métodos

**RegisterWeapon(string name, string prefabPath, float price, float reliability) : void**
```c
weaponSystem.RegisterWeapon(
    "Desert Eagle",
    "Prefabs/Weapons/DesertEagle.et",
    7500,
    0.92
);
```

**GetWeaponData(string weaponName) : NL_WeaponData**
```c
NL_WeaponData data = weaponSystem.GetWeaponData("AK-47");
Print(string.Format("Precio: %1", data.GetPrice()));
```

**GetAllWeapons() : array<ref NL_WeaponData>**
```c
array<ref NL_WeaponData> weapons = weaponSystem.GetAllWeapons();
```

**CanCraftWeapon(NL_PlayerData player, string weaponName) : bool**
```c
if (weaponSystem.CanCraftWeapon(player, "AK-47")) {
    Print("El jugador puede craftear esta arma");
}
```

**CraftWeapon(NL_PlayerData player, string weaponName) : NL_WeaponOwnership**
```c
NL_WeaponOwnership weapon = weaponSystem.CraftWeapon(player, "AK-47");
if (weapon) {
    Print("Arma crafteada exitosamente");
}
```

**PurchaseWeapon(NL_PlayerData player, string weaponName, NL_EconomySystem economy) : bool**
```c
if (weaponSystem.PurchaseWeapon(player, "M4A1", economy)) {
    Print("Arma comprada exitosamente");
}
```

### NL_WeaponData

**Métodos:**
```c
string GetName();
string GetPrefabPath();
float GetPrice();
float GetReliability();
float GetCraftingCost();
```

### NL_WeaponOwnership

**Métodos:**
```c
string GetWeaponName();
float GetDurability();
void DegradeDurability(float amount);
void AddKill();
int GetKills();
bool IsOperational(); // Returns true if durability > 10%
```

**Ejemplo:**
```c
NL_WeaponOwnership weapon = new NL_WeaponOwnership("AK-47", 0.9);
weapon.AddKill();
weapon.DegradeDurability(0.05);

if (!weapon.IsOperational()) {
    Print("Arma necesita reparación");
}
```

---

## Territory System

### NL_TerritorySystem

Gestiona territorios y capturas.

#### Métodos

**CreateTerritory(string name, vector position, float radius, float income) : NL_Territory**
```c
NL_Territory territory = territorySystem.CreateTerritory(
    "Zona Industrial",
    "5000 50 5000",
    500,    // Radio en metros
    1000    // Ingreso por período
);
```

**GetAllTerritories() : array<ref NL_Territory>**
```c
array<ref NL_Territory> territories = territorySystem.GetAllTerritories();
```

**GetTerritoryAtPosition(vector position) : NL_Territory**
```c
NL_Territory territory = territorySystem.GetTerritoryAtPosition(playerPos);
if (territory) {
    Print(string.Format("En territorio: %1", territory.GetName()));
}
```

**UpdateTerritories(float deltaTime) : void**
```c
// Llamar cada frame o tick
territorySystem.UpdateTerritories(deltaTime);
```

### NL_Territory

**Métodos:**
```c
string GetName();
vector GetPosition();
float GetRadius();
int GetOwnerFactionId();
void SetOwnerFaction(int factionId);
float GetIncome();
void StartCapture(int factionId);
void UpdateCapture(float deltaTime, int factionId);
```

**Ejemplo de captura:**
```c
NL_Territory territory = territorySystem.GetTerritoryAtPosition(playerPos);
if (territory) {
    int playerFaction = player.GetFactionId();
    
    if (territory.GetOwnerFactionId() != playerFaction) {
        territory.StartCapture(playerFaction);
    }
}
```

---

## Eventos

### Extender el Game Mode

```c
class MyCustomGameMode : NL_GameModeBase
{
    override void OnInit()
    {
        super.OnInit();
        Print("Mi modo de juego personalizado iniciado");
    }
    
    override void OnPlayerConnected(int playerId)
    {
        super.OnPlayerConnected(playerId);
        
        // Tu lógica personalizada
        NL_PlayerData data = GetPlayerData(playerId);
        GetFactionSystem().AssignPlayerToFaction(playerId, 3); // Todos empiezan como civiles
    }
    
    override void OnPlayerDisconnected(int playerId, KickCauseCode cause, int timeout)
    {
        super.OnPlayerDisconnected(playerId, cause, timeout);
        
        // Guardar datos del jugador, etc.
    }
}
```

## Componentes Personalizados

### Crear un Componente de Jugador Personalizado

```c
class MyPlayerComponent : NL_PlayerComponent
{
    override void EOnInit(IEntity owner)
    {
        super.EOnInit(owner);
        
        // Tu inicialización personalizada
    }
}
```

---

## Notas

- Todos los métodos que devuelven `bool` indican éxito (true) o fallo (false)
- Los índices de facciones comienzan en 0
- Los valores de dinero son de tipo `float` para mayor precisión
- Los vectores de posición siguen el formato "X Y Z" en cadenas o `vector` en código

## Ejemplos Completos

Ver [EXAMPLES.md](EXAMPLES.md) para ejemplos completos de uso.
