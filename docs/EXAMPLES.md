# Ejemplos de Uso - NarcosLife Framework

## Índice
- [Configuración Básica](#configuración-básica)
- [Sistema de Economía](#sistema-de-economía)
- [Sistema de Facciones](#sistema-de-facciones)
- [Sistema de Armas](#sistema-de-armas)
- [Sistema de Territorios](#sistema-de-territorios)
- [Modo de Juego Personalizado](#modo-de-juego-personalizado)

---

## Configuración Básica

### Crear un Servidor NarcosLife Simple

```c
class SimpleNarcosLifeMode : NL_GameModeBase
{
    override void OnInit()
    {
        super.OnInit();
        
        Print("[MiServidor] Iniciando servidor NarcosLife simple", LogLevel.NORMAL);
        
        // Configurar tiendas
        SetupShops();
        
        // Configurar territorios
        SetupTerritories();
    }
    
    void SetupShops()
    {
        // Crear tienda de armas
        NL_Shop weaponShop = new NL_Shop("Armeria Central", "5000 50 5000");
        weaponShop.AddItem(new NL_ShopItem("Glock 17", "Prefabs/Weapons/Pistols/Glock17.et", 5000));
        weaponShop.AddItem(new NL_ShopItem("AK-47", "Prefabs/Weapons/Rifles/AK47.et", 15000));
        GetEconomySystem().RegisterShop(weaponShop);
        
        // Crear tienda de vehículos
        NL_Shop vehicleShop = new NL_Shop("Concesionario", "4500 50 4500");
        vehicleShop.AddItem(new NL_ShopItem("Sedan", "Prefabs/Vehicles/Sedan.et", 25000));
        GetEconomySystem().RegisterShop(vehicleShop);
    }
    
    void SetupTerritories()
    {
        // Crear territorio con sistema de territorios (necesita ser implementado)
        Print("[MiServidor] Territorios configurados", LogLevel.NORMAL);
    }
}
```

---

## Sistema de Economía

### Ejemplo 1: Dar Dinero Inicial Personalizado por Facción

```c
class EconomyExampleMode : NL_GameModeBase
{
    override void OnPlayerConnected(int playerId)
    {
        super.OnPlayerConnected(playerId);
        
        NL_PlayerData playerData = GetPlayerData(playerId);
        if (!playerData)
            return;
        
        // Asignar facción aleatoria
        int randomFaction = Math.RandomInt(0, 4);
        playerData.SetFactionId(randomFaction);
        
        // Dinero inicial según facción
        float startMoney;
        switch (randomFaction) {
            case 0: // Carteles
                startMoney = 10000;
                break;
            case 1: // Policia
                startMoney = 8000;
                break;
            case 2: // FARC
                startMoney = 6000;
                break;
            case 3: // Civiles
                startMoney = 5000;
                break;
            default:
                startMoney = 5000;
        }
        
        playerData.SetMoney(startMoney);
        Print(string.Format("[Economia] Jugador %1 inicia con $%2 en facción %3", 
            playerId, startMoney, randomFaction), LogLevel.NORMAL);
    }
}
```

### Ejemplo 2: Sistema de Bonos por Actividad

```c
class BonusSystemMode : NL_GameModeBase
{
    // Llamar desde algún evento de kill
    void OnPlayerKill(int killerId, int victimId)
    {
        NL_PlayerData killer = GetPlayerData(killerId);
        NL_PlayerData victim = GetPlayerData(victimId);
        
        if (!killer || !victim)
            return;
        
        // Bono por kill
        float killBonus = 500;
        
        // Bono extra si es enemigo de facción
        if (GetFactionSystem().AreEnemies(killerId, victimId))
        {
            killBonus += 1000;
        }
        
        killer.AddMoney(killBonus);
        killer.AddKill();
        victim.AddDeath();
        
        Print(string.Format("[Bonos] Jugador %1 recibe $%2 por kill", 
            killerId, killBonus), LogLevel.NORMAL);
    }
}
```

### Ejemplo 3: Sistema de Impuestos

```c
class TaxSystemMode : NL_GameModeBase
{
    protected float m_fTaxInterval = 600; // 10 minutos
    protected float m_fLastTaxTime = 0;
    
    override void EOnFrame(IEntity owner, float timeSlice)
    {
        super.EOnFrame(owner, timeSlice);
        
        float currentTime = GetGame().GetWorld().GetWorldTime();
        
        if (currentTime - m_fLastTaxTime >= m_fTaxInterval)
        {
            CollectTaxes();
            m_fLastTaxTime = currentTime;
        }
    }
    
    void CollectTaxes()
    {
        // Obtener todos los jugadores (implementación simplificada)
        // En realidad necesitarías iterar sobre jugadores conectados
        
        Print("[Impuestos] Cobrando impuestos a todos los jugadores", LogLevel.NORMAL);
        
        // Ejemplo: cobrar 5% del dinero actual
        // foreach (NL_PlayerData player : allPlayers)
        // {
        //     float tax = player.GetMoney() * 0.05;
        //     player.RemoveMoney(tax);
        //     Print(string.Format("[Impuestos] Cobrado $%1 a jugador %2", tax, player.GetPlayerId()));
        // }
    }
}
```

---

## Sistema de Facciones

### Ejemplo 1: Guerra de Facciones Automática

```c
class FactionWarMode : NL_GameModeBase
{
    override void OnInit()
    {
        super.OnInit();
        
        // Configurar enemistades automáticas
        SetupFactionRelations();
    }
    
    void SetupFactionRelations()
    {
        NL_Faction carteles = GetFactionSystem().GetFaction(0);
        NL_Faction policia = GetFactionSystem().GetFaction(1);
        NL_Faction farc = GetFactionSystem().GetFaction(2);
        
        // Carteles vs Policia
        carteles.AddEnemy(1);
        policia.AddEnemy(0);
        
        // FARC vs Policia
        farc.AddEnemy(1);
        policia.AddEnemy(2);
        
        // Carteles y FARC son neutrales (no aliados ni enemigos)
        
        Print("[Facciones] Relaciones configuradas", LogLevel.NORMAL);
    }
    
    void OnPlayerKill(int killerId, int victimId)
    {
        if (GetFactionSystem().AreEnemies(killerId, victimId))
        {
            // Dar puntos/reputación a la facción del killer
            NL_PlayerData killer = GetPlayerData(killerId);
            int killerFaction = killer.GetFactionId();
            
            NL_Faction faction = GetFactionSystem().GetFaction(killerFaction);
            if (faction)
            {
                faction.AddMoney(100); // La facción gana dinero
                Print(string.Format("[Guerra] Facción %1 gana $100 por kill enemigo", 
                    faction.GetName()), LogLevel.NORMAL);
            }
        }
    }
}
```

### Ejemplo 2: Sistema de Reclutamiento

```c
class RecruitmentSystemMode : NL_GameModeBase
{
    bool TryRecruitPlayer(int recruiterId, int targetId, int factionId)
    {
        NL_PlayerData recruiter = GetPlayerData(recruiterId);
        NL_PlayerData target = GetPlayerData(targetId);
        
        if (!recruiter || !target)
            return false;
        
        // Verificar que el reclutador esté en la facción
        if (recruiter.GetFactionId() != factionId)
        {
            Print("[Reclutamiento] El reclutador no pertenece a esta facción", LogLevel.WARNING);
            return false;
        }
        
        // Verificar que el target no tenga facción o sea civil
        int currentFaction = target.GetFactionId();
        if (currentFaction != -1 && currentFaction != 3)
        {
            Print("[Reclutamiento] El jugador ya tiene una facción", LogLevel.WARNING);
            return false;
        }
        
        // Costo de reclutamiento
        float recruitmentCost = 2000;
        if (!recruiter.RemoveMoney(recruitmentCost))
        {
            Print("[Reclutamiento] Fondos insuficientes", LogLevel.WARNING);
            return false;
        }
        
        // Reclutar
        GetFactionSystem().AssignPlayerToFaction(targetId, factionId);
        
        // Bono de bienvenida
        target.AddMoney(1000);
        
        Print(string.Format("[Reclutamiento] Jugador %1 reclutado por %2 en facción %3", 
            targetId, recruiterId, factionId), LogLevel.NORMAL);
        
        return true;
    }
}
```

---

## Sistema de Armas

### Ejemplo 1: Tienda de Armas con Descuentos por Facción

```c
class WeaponShopMode : NL_GameModeBase
{
    bool PurchaseWeaponWithDiscount(int playerId, string weaponName)
    {
        NL_PlayerData player = GetPlayerData(playerId);
        if (!player)
            return false;
        
        NL_WeaponData weaponData = GetWeaponSystem().GetWeaponData(weaponName);
        if (!weaponData)
            return false;
        
        float basePrice = weaponData.GetPrice();
        float finalPrice = basePrice;
        
        // Descuento según facción
        int factionId = player.GetFactionId();
        switch (factionId) {
            case 0: // Carteles - 10% descuento
                finalPrice *= 0.9;
                break;
            case 1: // Policia - 20% descuento
                finalPrice *= 0.8;
                break;
            case 2: // FARC - 15% descuento
                finalPrice *= 0.85;
                break;
            // Civiles pagan precio completo
        }
        
        if (!GetEconomySystem().CanAfford(player, finalPrice))
        {
            Print(string.Format("[Tienda] Jugador %1 no puede pagar $%2", playerId, finalPrice), 
                LogLevel.WARNING);
            return false;
        }
        
        if (GetEconomySystem().ProcessTransaction(player, -finalPrice, "Compra: " + weaponName))
        {
            NL_WeaponOwnership weapon = new NL_WeaponOwnership(weaponName, weaponData.GetReliability());
            player.AddWeapon(weapon);
            
            Print(string.Format("[Tienda] Jugador %1 compró %2 por $%3 (desc: %4%)", 
                playerId, weaponName, finalPrice, (1 - finalPrice/basePrice) * 100), 
                LogLevel.NORMAL);
            return true;
        }
        
        return false;
    }
}
```

### Ejemplo 2: Sistema de Degradación Realista

```c
class WeaponDegradationMode : NL_GameModeBase
{
    void OnWeaponFired(int playerId, NL_WeaponOwnership weapon)
    {
        if (!weapon)
            return;
        
        // Degradar arma cada disparo
        float degradation = 0.001; // 0.1% por disparo
        weapon.DegradeDurability(degradation);
        
        // Verificar si necesita mantenimiento
        if (!weapon.IsOperational())
        {
            Print(string.Format("[Armas] Arma de jugador %1 necesita reparación", playerId), 
                LogLevel.WARNING);
            // Aquí podrías deshabilitar el arma o reducir precisión
        }
    }
    
    bool RepairWeapon(int playerId, NL_WeaponOwnership weapon)
    {
        NL_PlayerData player = GetPlayerData(playerId);
        if (!player || !weapon)
            return false;
        
        float repairCost = 1000;
        
        if (!GetEconomySystem().ProcessTransaction(player, -repairCost, "Reparación de arma"))
            return false;
        
        // Restaurar durabilidad al 90%
        // (En la implementación real necesitarías un método SetDurability)
        Print(string.Format("[Armas] Arma reparada para jugador %1", playerId), LogLevel.NORMAL);
        return true;
    }
}
```

---

## Sistema de Territorios

### Ejemplo 1: Control de Territorios con Beneficios

```c
class TerritoryControlMode : NL_GameModeBase
{
    protected ref NL_TerritorySystem m_TerritorySystem;
    protected float m_fIncomeInterval = 300; // 5 minutos
    protected float m_fLastIncomeTime = 0;
    
    override void OnInit()
    {
        super.OnInit();
        
        m_TerritorySystem = new NL_TerritorySystem();
        SetupTerritories();
    }
    
    void SetupTerritories()
    {
        // Zona de Drogas
        m_TerritorySystem.CreateTerritory("Plantación", "1000 50 1000", 500, 2000);
        
        // Zona Industrial
        m_TerritorySystem.CreateTerritory("Industrial", "5000 50 5000", 800, 1500);
        
        // Puerto
        m_TerritorySystem.CreateTerritory("Puerto", "8000 10 3000", 600, 3000);
        
        Print("[Territorios] 3 territorios creados", LogLevel.NORMAL);
    }
    
    override void EOnFrame(IEntity owner, float timeSlice)
    {
        super.EOnFrame(owner, timeSlice);
        
        float currentTime = GetGame().GetWorld().GetWorldTime();
        
        // Procesar ingresos territoriales
        if (currentTime - m_fLastIncomeTime >= m_fIncomeInterval)
        {
            ProcessTerritoryIncome();
            m_fLastIncomeTime = currentTime;
        }
        
        // Actualizar capturas
        m_TerritorySystem.UpdateTerritories(timeSlice);
    }
    
    void ProcessTerritoryIncome()
    {
        array<ref NL_Territory> territories = m_TerritorySystem.GetAllTerritories();
        
        foreach (NL_Territory territory : territories)
        {
            int ownerFaction = territory.GetOwnerFactionId();
            if (ownerFaction == -1)
                continue;
            
            NL_Faction faction = GetFactionSystem().GetFaction(ownerFaction);
            if (faction)
            {
                float income = territory.GetIncome();
                faction.AddMoney(income);
                
                Print(string.Format("[Territorios] Facción %1 recibe $%2 de territorio %3", 
                    faction.GetName(), income, territory.GetName()), LogLevel.NORMAL);
                
                // Distribuir entre miembros
                DistributeIncomeToMembers(faction, income);
            }
        }
    }
    
    void DistributeIncomeToMembers(NL_Faction faction, float totalIncome)
    {
        array<int> members = faction.GetMembers();
        if (members.Count() == 0)
            return;
        
        float incomePerMember = totalIncome / members.Count();
        
        foreach (int memberId : members)
        {
            NL_PlayerData player = GetPlayerData(memberId);
            if (player)
            {
                player.AddMoney(incomePerMember);
            }
        }
    }
}
```

---

## Modo de Juego Personalizado

### Ejemplo Completo: Modo NarcosLife Full

```c
class FullNarcosLifeMode : NL_GameModeBase
{
    protected ref NL_TerritorySystem m_TerritorySystem;
    protected ref NL_UIManager m_UIManager;
    protected float m_fUpdateInterval = 1.0;
    protected float m_fLastUpdate = 0;
    
    override void OnInit()
    {
        super.OnInit();
        
        Print("========================================", LogLevel.NORMAL);
        Print("[NarcosLife FULL] Inicializando servidor completo", LogLevel.NORMAL);
        Print("========================================", LogLevel.NORMAL);
        
        m_TerritorySystem = new NL_TerritorySystem();
        m_UIManager = new NL_UIManager();
        
        InitializeFullServer();
    }
    
    void InitializeFullServer()
    {
        // Configurar tiendas
        SetupShops();
        
        // Configurar territorios
        SetupTerritories();
        
        // Configurar armas personalizadas
        SetupCustomWeapons();
        
        Print("[NarcosLife FULL] Servidor completamente inicializado", LogLevel.NORMAL);
    }
    
    void SetupShops()
    {
        // Tiendas de armas legales
        NL_Shop legalWeapons = new NL_Shop("Armeria Legal", "5000 50 5000");
        legalWeapons.AddItem(new NL_ShopItem("Glock 17", "Prefabs/Weapons/Pistols/Glock17.et", 5000, 20));
        legalWeapons.AddItem(new NL_ShopItem("Remington 870", "Prefabs/Weapons/Shotguns/Rem870.et", 8000, 10));
        GetEconomySystem().RegisterShop(legalWeapons);
        
        // Mercado negro
        NL_Shop blackMarket = new NL_Shop("Mercado Negro", "1500 45 8500");
        blackMarket.AddItem(new NL_ShopItem("AK-47", "Prefabs/Weapons/Rifles/AK47.et", 12000, 5));
        blackMarket.AddItem(new NL_ShopItem("MP5", "Prefabs/Weapons/SMGs/MP5.et", 10000, 8));
        GetEconomySystem().RegisterShop(blackMarket);
        
        Print("[Setup] Tiendas configuradas", LogLevel.NORMAL);
    }
    
    void SetupTerritories()
    {
        m_TerritorySystem.CreateTerritory("Plantación de Coca", "1000 50 1000", 500, 3000);
        m_TerritorySystem.CreateTerritory("Laboratorio", "2000 55 2000", 400, 2500);
        m_TerritorySystem.CreateTerritory("Puerto de Contrabando", "8000 10 3000", 600, 4000);
        m_TerritorySystem.CreateTerritory("Punto de Venta", "6000 50 6000", 300, 1500);
        
        Print("[Setup] Territorios configurados", LogLevel.NORMAL);
    }
    
    void SetupCustomWeapons()
    {
        GetWeaponSystem().RegisterWeapon("Uzi", "Prefabs/Weapons/SMGs/Uzi.et", 9000, 0.75);
        GetWeaponSystem().RegisterWeapon("Barrett M82", "Prefabs/Weapons/Snipers/Barrett.et", 35000, 0.95);
        
        Print("[Setup] Armas personalizadas registradas", LogLevel.NORMAL);
    }
    
    override void OnPlayerConnected(int playerId)
    {
        super.OnPlayerConnected(playerId);
        
        NL_PlayerData player = GetPlayerData(playerId);
        if (!player)
            return;
        
        // Asignar a civiles por defecto
        GetFactionSystem().AssignPlayerToFaction(playerId, 3);
        
        // Notificación de bienvenida
        m_UIManager.ShowNotification(
            string.Format("Bienvenido jugador %1! Tienes $%2 para empezar.", 
            playerId, player.GetMoney())
        );
        
        Print(string.Format("[Servidor] Jugador %1 conectado y configurado", playerId), 
            LogLevel.NORMAL);
    }
    
    override void EOnFrame(IEntity owner, float timeSlice)
    {
        super.EOnFrame(owner, timeSlice);
        
        float currentTime = GetGame().GetWorld().GetWorldTime();
        
        if (currentTime - m_fLastUpdate >= m_fUpdateInterval)
        {
            UpdateGameSystems(timeSlice);
            m_fLastUpdate = currentTime;
        }
    }
    
    void UpdateGameSystems(float deltaTime)
    {
        // Actualizar territorios
        m_TerritorySystem.UpdateTerritories(deltaTime);
        
        // Procesar salarios cada intervalo configurado
        // (La implementación real necesitaría acceso a la lista de jugadores)
        
        // Actualizar UI para todos los jugadores
        UpdateAllPlayersUI();
    }
    
    void UpdateAllPlayersUI()
    {
        // Iterar sobre jugadores y actualizar UI
        // (Implementación simplificada)
    }
}
```

---

## Notas

- Estos ejemplos son ilustrativos y pueden requerir ajustes según la implementación específica de Arma Reforger
- Algunos métodos como `EOnFrame` necesitan ser correctamente integrados con el sistema de eventos de Arma Reforger
- La iteración sobre jugadores conectados requiere acceso a la API del servidor de Arma Reforger
- Para producción, considera añadir validación adicional y manejo de errores

## Próximos Pasos

1. Implementa uno de estos ejemplos en tu servidor
2. Modifícalo según tus necesidades específicas
3. Prueba exhaustivamente
4. Añade persistencia de datos (base de datos)
5. Implementa UI personalizada

Para más información, consulta la [Documentación API](API.md).
