# NarcosLife Framework para Arma Reforger

Un framework completo para crear servidores de roleplay tipo NarcosLife en Arma Reforger.

## 🎮 Descripción

Este framework proporciona un sistema completo para crear experiencias de roleplay basadas en el concepto de NarcosLife, incluyendo sistemas de economía, facciones, armas, territorios y más.

## ✨ Características Principales

### 💰 Sistema de Economía
- Sistema monetario completo
- Tiendas configurables
- Salarios automáticos
- Transacciones seguras
- Sistema de stock para items

### 🔫 Sistema de Armas
- Registro de armas personalizable
- Sistema de compra y venta
- Crafteo de armas
- Durabilidad de armas
- Estadísticas de armas por jugador

### 👥 Sistema de Facciones
- Facciones predefinidas (Carteles, Policía, FARC, Civiles)
- Sistema de alianzas y enemigos
- Dinero de facción
- Territorios de facción
- Gestión de miembros

### 🗺️ Sistema de Territorios
- Control de territorios
- Sistema de captura
- Beneficios económicos por territorio
- Zonas de influencia

### 📊 Sistema de Jugadores
- Datos persistentes de jugador
- Estadísticas (kills, deaths, tiempo de juego)
- Inventario de armas
- Balance económico

## 📁 Estructura del Proyecto

```
Addons/NarcosLifeFramework/
├── Scripts/
│   ├── Game/
│   │   ├── GameMode/          # Modo de juego base y datos de jugador
│   │   ├── Economy/           # Sistema económico
│   │   ├── Factions/          # Sistema de facciones
│   │   └── Weapons/           # Sistema de armas
│   ├── Components/            # Componentes de entidades
│   ├── Systems/               # Sistemas adicionales
│   └── UI/                    # Gestión de interfaz
├── Configs/
│   ├── config.conf            # Configuración principal
│   ├── shops.conf             # Configuración de tiendas
│   └── factions.conf          # Configuración de facciones
├── Prefabs/                   # Prefabs del juego
├── Worlds/                    # Mundos/mapas
└── UI/                        # Layouts de UI
```

## 🚀 Instalación

1. Clona este repositorio en tu directorio de mods de Arma Reforger
2. Configura el archivo `addon.gproj` según tus necesidades
3. Ajusta las configuraciones en `Addons/NarcosLifeFramework/Configs/`
4. Carga el mod en Arma Reforger Workbench

## ⚙️ Configuración

### Configuración Principal (`config.conf`)

```
SCR_NarcosLifeConfig {
 m_sModName "NarcosLife Framework"
 m_sModVersion "1.0.0"
 m_bEnableDebugMode 0
 
 m_EconomyConfig {
  m_iStartingMoney 5000        # Dinero inicial
  m_fSalaryInterval 300        # Intervalo de salario (segundos)
  m_fSalaryAmount 500          # Cantidad de salario
 }
}
```

### Facciones Predefinidas

1. **Los Carteles** - Organización de tráfico de drogas
2. **Policía Nacional** - Fuerza policial
3. **FARC** - Fuerzas revolucionarias
4. **Civiles** - Población civil

## 🛠️ Uso del Framework

### Crear un Modo de Juego Personalizado

```c
class MyNarcosLifeMode : NL_GameModeBase
{
 override void OnInit()
 {
  super.OnInit();
  
  // Tu código personalizado aquí
 }
}
```

### Registrar Armas Personalizadas

```c
GetWeaponSystem().RegisterWeapon(
 "Mi Arma",
 "Prefabs/Weapons/MiArma.et",
 10000,  // Precio
 0.90    // Fiabilidad
);
```

### Crear Tiendas

```c
NL_Shop shop = new NL_Shop("Mi Tienda", "5000 50 5000");
shop.AddItem(new NL_ShopItem("AK-47", "Prefabs/Weapons/AK47.et", 15000));
GetEconomySystem().RegisterShop(shop);
```

## 📋 Sistemas Principales

### NL_GameModeBase
Clase base del modo de juego que gestiona todos los sistemas.

**Métodos principales:**
- `GetPlayerData(int playerId)` - Obtiene datos de jugador
- `GetEconomySystem()` - Accede al sistema económico
- `GetFactionSystem()` - Accede al sistema de facciones
- `GetWeaponSystem()` - Accede al sistema de armas

### NL_EconomySystem
Gestiona la economía del servidor.

**Funcionalidades:**
- Procesamiento de transacciones
- Gestión de tiendas
- Sistema de salarios
- Verificación de fondos

### NL_FactionSystem
Controla las facciones y sus relaciones.

**Funcionalidades:**
- Asignación de jugadores a facciones
- Gestión de alianzas y enemigos
- Dinero de facción
- Territorios de facción

### NL_WeaponSystem
Sistema completo de gestión de armas.

**Funcionalidades:**
- Registro de armas
- Compra y venta
- Crafteo
- Sistema de durabilidad

## 🎯 Características Futuras

- [ ] Sistema de drogas y plantaciones
- [ ] Misiones dinámicas
- [ ] Sistema de vehículos mejorado
- [ ] Integración con base de datos
- [ ] Sistema de respawn personalizado
- [ ] Sistema de prisión
- [ ] Raids y asaltos a bases
- [ ] Sistema de crafteo avanzado

## 🤝 Contribuir

Las contribuciones son bienvenidas. Por favor:

1. Fork el proyecto
2. Crea una rama para tu feature (`git checkout -b feature/AmazingFeature`)
3. Commit tus cambios (`git commit -m 'Add some AmazingFeature'`)
4. Push a la rama (`git push origin feature/AmazingFeature`)
5. Abre un Pull Request

## 📝 Licencia

Este proyecto está bajo la Licencia MIT. Ver el archivo `LICENSE` para más detalles.

## 👨‍💻 Autor

**Arribas22**

## 🙏 Agradecimientos

- Comunidad de Arma Reforger
- Desarrolladores del concepto NarcosLife original
- Bohemia Interactive por Arma Reforger

## 📞 Soporte

Para soporte, preguntas o sugerencias, por favor abre un issue en GitHub.

---

**Nota:** Este es un framework en desarrollo. Algunas características pueden no estar completamente implementadas y requieren integración con los sistemas nativos de Arma Reforger.