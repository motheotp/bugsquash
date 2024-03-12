project(BugSquashLib)

set(SOURCE_FILES MainFrame.cpp MainFrame.h pch.h BugSquashView.cpp BugSquashView.h Scoreboard.cpp Scoreboard.h Level.cpp Level.h LevelManager.cpp LevelManager.h ids.h Item.cpp Item.h Bug.cpp Bug.h Game.cpp Game.h Program.cpp Program.h BugNull.cpp BugNull.h BugGarbage.cpp BugGarbage.h BugRedundancy.cpp BugRedundancy.h BugFeature.cpp BugFeature.h BugFatFunc.cpp BugFatFunc.h CodeDlg.cpp CodeDlg.h BugGarbageFat.cpp BugGarbageFat.h BugNullFat.cpp BugNullFat.h BugZombie.cpp BugZombie.h BugRace.cpp BugRace.h ItemVisitor.h ZombieReviver.cpp ZombieReviver.h RaceOrderChecker.cpp RaceOrderChecker.h LevelEndCheck.cpp LevelEndCheck.h)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} MainFrame.cpp MainFrame.h)

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)
