# Guía de Inicio Rápido - NarcosLife Framework

Esta guía te ayudará a tener el framework funcionando en menos de 15 minutos.

## ⚡ Instalación Rápida

### 1. Descarga el Framework
```bash
git clone https://github.com/Arribas22/dev1234.git
cd dev1234
```

### 2. Configuración Mínima

Edita `Addons/NarcosLifeFramework/Configs/config.conf` con tus valores preferidos:

```c
SCR_NarcosLifeConfig {
 m_sModName "Mi Servidor NarcosLife"
 m_EconomyConfig {
  m_iStartingMoney 5000
 }
}
```

### 3. Abre en Workbench

1. Abre Arma Reforger Workbench
2. File → Open → Selecciona `addon.gproj`
3. Espera a que cargue

### 4. Crea un Mundo de Prueba

1. World Editor → New World
2. Hierarchy → Right Click → Create → Game Mode
3. Selecciona `NL_GameModeBase`
4. Añade spawn points
5. Guarda el mundo

### 5. Prueba Local

1. World Editor → Play
2. Verifica en la consola:
```
[NarcosLife] Game Mode initialized
[NarcosLife] Economy System initialized
[NarcosLife] Faction System initialized
[NarcosLife] Weapon System initialized
```

## 🎮 Primeros Pasos en el Juego

### Verificar tu Dinero
Tu personaje debería empezar con $5000 (configurable).

### Unirse a una Facción
Por defecto, empiezas como "Civiles". Las facciones disponibles son:
- Los Carteles (ID: 0)
- Policía Nacional (ID: 1)
- FARC (ID: 2)
- Civiles (ID: 3)

### Buscar Tiendas
Las tiendas están configuradas en `Configs/shops.conf`. Por defecto:
- **Armeria Central**: Coordenadas 5000, 50, 5000
- **Tienda Ilegal**: Coordenadas 3000, 45, 8000

## 🛠️ Personalización Rápida

### Cambiar Dinero Inicial
En `NL_GameModeBase`:
```c
[Attribute("10000", UIWidgets.EditBox, "Starting money for players")]
protected int m_iStartingMoney;
```

### Añadir una Tienda
En `Configs/shops.conf`:
```c
NL_ShopEntry {
 m_sName "Mi Tienda"
 m_vPosition "X Y Z"
 m_Items {
  NL_ShopItemEntry {
   m_sName "Item"
   m_sPrefab "Ruta/Al/Prefab.et"
   m_fPrice 1000
  }
 }
}
```

### Añadir un Arma Nueva
En tu código:
```c
GetWeaponSystem().RegisterWeapon(
 "Mi Arma",
 "Prefabs/Weapons/MiArma.et",
 5000,  // Precio
 0.90   // Fiabilidad
);
```

## 📚 Próximos Pasos

1. **Lee la documentación completa**: [README.md](README.md)
2. **Explora ejemplos**: [docs/EXAMPLES.md](docs/EXAMPLES.md)
3. **Consulta la API**: [docs/API.md](docs/API.md)
4. **Personaliza tu servidor**

## 🆘 Problemas Comunes

### "No se carga el addon"
- Verifica que el GUID en `addon.gproj` sea único
- Revisa la sintaxis de archivos `.conf`

### "No aparecen logs"
- Activa debug mode en `config.conf`:
```c
m_bEnableDebugMode 1
```

### "Errores de compilación"
- Verifica que todos los archivos `.c` estén en las rutas correctas
- Comprueba que los nombres de clase coincidan con los archivos

## 💬 Soporte

¿Necesitas ayuda? 
- Abre un issue en GitHub
- Revisa la documentación en `/docs`
- Lee el archivo [CONTRIBUTING.md](CONTRIBUTING.md)

## ✅ Checklist de Verificación

Después de seguir esta guía, deberías tener:

- [ ] Framework clonado y abierto en Workbench
- [ ] Configuración básica personalizada
- [ ] Mundo de prueba creado
- [ ] Modo de juego funcionando
- [ ] Logs mostrando inicialización correcta
- [ ] Jugador spawneado con dinero inicial

¡Felicidades! Ahora tienes un servidor NarcosLife básico funcionando. 🎉

---

**Tiempo estimado**: 10-15 minutos  
**Dificultad**: Principiante  
**Siguiente paso**: Explorar [EXAMPLES.md](docs/EXAMPLES.md) para características avanzadas
