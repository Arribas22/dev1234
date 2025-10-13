# Guía de Instalación - NarcosLife Framework

## Requisitos Previos

- Arma Reforger instalado
- Arma Reforger Workbench instalado
- Conocimientos básicos de modding en Arma Reforger

## Pasos de Instalación

### 1. Preparar el Entorno

1. Abre Arma Reforger Workbench
2. Navega a tu directorio de proyectos de mods

### 2. Instalar el Framework

```bash
# Opción 1: Clonar desde Git
git clone https://github.com/Arribas22/dev1234.git

# Opción 2: Descargar y extraer el ZIP
# Descarga el archivo ZIP desde GitHub
# Extrae en tu directorio de mods
```

### 3. Configurar el Proyecto

1. Abre `addon.gproj` en un editor de texto
2. Ajusta el GUID si es necesario (debe ser único)
3. Verifica las rutas de configuración

```json
{
 "name": "NarcosLife Framework",
 "guid": "5F5A8D6E8B1C4A2F",  // Cambia este GUID
 "title": "NarcosLife Framework for Arma Reforger",
 "version": "1.0.0",
 "author": "Tu Nombre",
 "dependencies": [],
 "configurations": [
  "Addons/NarcosLifeFramework/Configs/config.conf"
 ]
}
```

### 4. Configurar Parámetros del Juego

Edita `Addons/NarcosLifeFramework/Configs/config.conf`:

```c
SCR_NarcosLifeConfig {
 m_sModName "Mi Servidor NarcosLife"
 m_sModVersion "1.0.0"
 m_bEnableDebugMode 1  // Activa modo debug durante desarrollo
 
 m_EconomyConfig {
  m_iStartingMoney 5000      // Dinero inicial
  m_fSalaryInterval 300      // 5 minutos
  m_fSalaryAmount 500        // $500 por salario
 }
 
 m_WeaponConfig {
  m_bEnableWeaponShops 1
  m_bEnableWeaponCrafting 1
  m_fWeaponDegradation 0.1   // 10% degradación
 }
 
 m_FactionConfig {
  m_bEnableFactionSystem 1
  m_iMaxFactionsPerPlayer 1
  m_bEnableFactionWars 1
 }
}
```

### 5. Configurar Facciones

Edita `Addons/NarcosLifeFramework/Configs/factions.conf` para personalizar facciones:

```c
NL_FactionEntry {
 m_iId 0
 m_sName "Nombre de Facción"
 m_sDescription "Descripción"
 m_sColor "R G B"  // Valores entre 0 y 1
 m_Allies {1, 2}   // IDs de facciones aliadas
 m_Enemies {3}     // IDs de facciones enemigas
 m_fStartingMoney 50000
}
```

### 6. Configurar Tiendas

Edita `Addons/NarcosLifeFramework/Configs/shops.conf`:

```c
NL_ShopEntry {
 m_sName "Nombre de Tienda"
 m_vPosition "X Y Z"  // Coordenadas en el mapa
 m_Items {
  NL_ShopItemEntry {
   m_sName "Item"
   m_sPrefab "Ruta/Al/Prefab.et"
   m_fPrice 1000
   m_iStock -1  // -1 = stock ilimitado
  }
 }
}
```

### 7. Cargar en Workbench

1. Abre Arma Reforger Workbench
2. File → Open → Selecciona `addon.gproj`
3. Verifica que no haya errores en la consola

### 8. Configurar el Mundo

1. Crea o abre un mundo en Workbench
2. Agrega el GameMode:
   - Hierarchy → Right Click → Create → Game Mode
   - Selecciona `NL_GameModeBase`

3. Configura spawn points y otros elementos necesarios

### 9. Probar el Mod

#### Modo Local

1. En Workbench: World Editor → Play
2. Verifica la consola para mensajes de inicialización:
   ```
   [NarcosLife] Game Mode initialized
   [NarcosLife] Economy System initialized
   [NarcosLife] Faction System initialized
   [NarcosLife] Weapon System initialized
   ```

#### Servidor Dedicado

1. Exporta el addon desde Workbench
2. Copia los archivos al servidor
3. Añade el mod a la configuración del servidor
4. Inicia el servidor y verifica logs

### 10. Verificación

Comprueba que todo funciona:

- [ ] El modo de juego se carga correctamente
- [ ] Los jugadores reciben dinero inicial
- [ ] Los sistemas de economía funcionan
- [ ] Las facciones están disponibles
- [ ] Las tiendas aparecen en el mapa
- [ ] Los logs muestran inicialización exitosa

## Solución de Problemas

### Error: "No se puede cargar el addon"
- Verifica que el GUID sea único
- Comprueba la sintaxis de los archivos .conf
- Revisa las rutas de los prefabs

### Error: "Game Mode no se inicia"
- Asegúrate de que NL_GameModeBase esté correctamente extendiendo SCR_BaseGameMode
- Verifica que todos los scripts estén en las rutas correctas

### No aparecen logs de NarcosLife
- Activa el modo debug en config.conf
- Verifica que los niveles de log estén configurados correctamente

## Siguientes Pasos

Una vez instalado correctamente:

1. Lee la [Guía de Uso](USAGE.md)
2. Consulta la [API Documentation](API.md)
3. Revisa los [Ejemplos](EXAMPLES.md)

## Soporte

Si encuentras problemas:
- Revisa los issues existentes en GitHub
- Crea un nuevo issue con información detallada
- Incluye logs y configuración relevante
