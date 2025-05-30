#include <iostream>
#include <fstream> // Added for file operations
#include <iomanip>
#include <sstream>
#include <vector>
#include <queue>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <random>
#include <algorithm> // Required for std::max

using namespace std;

// Global log file stream
std::ofstream logFile;

// ====================================================================
// FORWARD DECLARATIONS
// ====================================================================
class Battlefield;
class Robot;
class GenericRobot;
class HideBot;
class JumpBot;
class LongShotBot;
class SemiAutoBot;
class ThirtyShotBot;
class ScoutBot;
class TrackBot;

// ====================================================================
// ABSTRACT BASE INTERFACES
// ====================================================================
class MovingRobot {
public:
    virtual void actionMove(Battlefield* battlefield) = 0;
    virtual ~MovingRobot() = default; // Added virtual destructor
};

class ShootingRobot {
public:
    virtual void actionFire(Battlefield* battlefield, int dx, int dy) = 0;
    virtual ~ShootingRobot() = default; // Added virtual destructor
};

class SeeingRobot {
public:
    virtual void actionLook(Battlefield* battlefield, int dx, int dy) = 0;
    virtual ~SeeingRobot() = default; // Added virtual destructor
};

class ThinkingRobot {
public:
    virtual void actionThink(Battlefield* battlefield) = 0;
    virtual ~ThinkingRobot() = default; // Added virtual destructor
};

// ====================================================================
// ROBOT CLASS DECLARATION (Header-like)
// ====================================================================
class Robot : public MovingRobot, public ShootingRobot, public SeeingRobot, public ThinkingRobot {
protected:
    int robotPositionX = -1;
    int robotPositionY = -1;
    string id_ = "";
    string robotType_ = "";
    string robotName_ = "";
    int numOfLives_ = 3;
    int numOfKills_ = 0;
    int shells_ = 10;
    int upgradeStage_ = 0;
    vector<bool> upgradedAreas_ = {false, false, false};
    bool isHidden_ = false;
    int hideDuration_ = 0;
    string trackedRobotId_ = "";
    int trackerCount_ = 0;
    int reentryAttempts_ = 0;

public:
    Robot(string id = "", int x = -1, int y = -1);
    virtual ~Robot();

    int x() const;
    void setX(int x);
    int y() const;
    void setY(int y);
    string id() const;
    void setId(string id);
    string robotType() const;
    void setRobotType(string robotType);
    string robotName() const;
    void setRobotName(string robotName);
    int numOfLives() const;
    void setNumOfLives(int numOfLives);
    int numOfKills() const;
    void setNumOfKills(int numOfKills);
    int getShells() const;
    void setShells(int s);
    void reduceLife();
    void incrementKills();
    bool isAlive() const;
    int getUpgradeStage() const { return upgradeStage_; }
    void setUpgradeStage(int stage) { upgradeStage_ = stage; }
    const vector<bool>& getUpgradedAreas() const { return upgradedAreas_; }
    void setUpgradedArea(int index, bool status) { upgradedAreas_[index] = status; }
    void setUpgradedAreas(const vector<bool>& areas) { upgradedAreas_ = areas; }
    bool isHidden() const { return isHidden_; }
    void setHidden(bool status) { isHidden_ = status; }
    int getHideDuration() const { return hideDuration_; }
    void setHideDuration(int duration) { hideDuration_ = duration; }
    string getTrackedRobotId() const { return trackedRobotId_; }
    void setTrackedRobotId(string id) { trackedRobotId_ = id; }
    int getTrackerCount() const { return trackerCount_; }
    void setTrackerCount(int count) { trackerCount_ = count; }
    void decrementTrackerCount() { if (trackerCount_ > 0) trackerCount_--; }
    int getReentryAttempts() const { return reentryAttempts_; }
    void setReentryAttempts(int attempts) { reentryAttempts_ = attempts; }
    void incrementReentryAttempts() { reentryAttempts_++; }

    friend ostream& operator<<(ostream& out, const Robot& r);

    virtual void setLocation(int x, int y) = 0;
    virtual void actions(Battlefield* battlefield) = 0;
    virtual void actionUpgrade(Battlefield* battlefield) = 0;
};

// ====================================================================
// GENERIC ROBOT CLASS DECLARATION (Header-like)
// ====================================================================
class GenericRobot : public Robot {
public:
    GenericRobot(string id = "", int x = -1, int y = -1);
    virtual ~GenericRobot();
    virtual void setLocation(int x, int y) override;
    virtual void actionThink(Battlefield* battlefield) override;
    virtual void actionLook(Battlefield* battlefield, int dx, int dy) override;
    virtual void actionFire(Battlefield* battlefield, int dx, int dy) override;
    virtual void actionMove(Battlefield* battlefield) override;
    virtual void actions(Battlefield* battlefield) override;
    virtual void actionUpgrade(Battlefield* battlefield) override;
};

// ====================================================================
// SPECIALIZED ROBOT CLASSES DECLARATION
// ====================================================================
class HideBot : public Robot {
private:
    int hideUses_ = 3;
public:
    HideBot(string id = "", int x = -1, int y = -1);
    virtual ~HideBot();
    virtual void setLocation(int x, int y) override;
    virtual void actionThink(Battlefield* battlefield) override;
    virtual void actionLook(Battlefield* battlefield, int dx, int dy) override;
    virtual void actionFire(Battlefield* battlefield, int dx, int dy) override;
    virtual void actionMove(Battlefield* battlefield) override;
    virtual void actions(Battlefield* battlefield) override;
    virtual void actionUpgrade(Battlefield* battlefield) override { /* No further upgrade */ }
};

class JumpBot : public Robot {
private:
    int jumpUses_ = 3;
public:
    JumpBot(string id = "", int x = -1, int y = -1);
    virtual ~JumpBot();
    virtual void setLocation(int x, int y) override;
    virtual void actionThink(Battlefield* battlefield) override;
    virtual void actionLook(Battlefield* battlefield, int dx, int dy) override;
    virtual void actionFire(Battlefield* battlefield, int dx, int dy) override;
    virtual void actionMove(Battlefield* battlefield) override;
    virtual void actions(Battlefield* battlefield) override;
    virtual void actionUpgrade(Battlefield* battlefield) override { /* No further upgrade */ }
};

class LongShotBot : public Robot {
public:
    LongShotBot(string id = "", int x = -1, int y = -1);
    virtual ~LongShotBot();
    virtual void setLocation(int x, int y) override;
    virtual void actionThink(Battlefield* battlefield) override;
    virtual void actionLook(Battlefield* battlefield, int dx, int dy) override;
    virtual void actionFire(Battlefield* battlefield, int dx, int dy) override;
    virtual void actionMove(Battlefield* battlefield) override;
    virtual void actions(Battlefield* battlefield) override;
    virtual void actionUpgrade(Battlefield* battlefield) override { /* No further upgrade */ }
};

class SemiAutoBot : public Robot {
public:
    SemiAutoBot(string id = "", int x = -1, int y = -1);
    virtual ~SemiAutoBot();
    virtual void setLocation(int x, int y) override;
    virtual void actionThink(Battlefield* battlefield) override;
    virtual void actionLook(Battlefield* battlefield, int dx, int dy) override;
    virtual void actionFire(Battlefield* battlefield, int dx, int dy) override;
    virtual void actionMove(Battlefield* battlefield) override;
    virtual void actions(Battlefield* battlefield) override;
    virtual void actionUpgrade(Battlefield* battlefield) override { /* No further upgrade */ }
};

class ThirtyShotBot : public Robot {
public:
    ThirtyShotBot(string id = "", int x = -1, int y = -1);
    virtual ~ThirtyShotBot();
    virtual void setLocation(int x, int y) override;
    virtual void actionThink(Battlefield* battlefield) override;
    virtual void actionLook(Battlefield* battlefield, int dx, int dy) override;
    virtual void actionFire(Battlefield* battlefield, int dx, int dy) override;
    virtual void actionMove(Battlefield* battlefield) override;
    virtual void actions(Battlefield* battlefield) override;
    virtual void actionUpgrade(Battlefield* battlefield) override { /* No further upgrade */ }
};

class ScoutBot : public Robot {
private:
    int fullScanUses_ = 3;
public:
    ScoutBot(string id = "", int x = -1, int y = -1);
    virtual ~ScoutBot();
    virtual void setLocation(int x, int y) override;
    virtual void actionThink(Battlefield* battlefield) override;
    virtual void actionLook(Battlefield* battlefield, int dx, int dy) override;
    virtual void actionFire(Battlefield* battlefield, int dx, int dy) override;
    virtual void actionMove(Battlefield* battlefield) override;
    virtual void actions(Battlefield* battlefield) override;
    virtual void actionUpgrade(Battlefield* battlefield) override { /* No further upgrade */ }
};

class TrackBot : public Robot {
public:
    TrackBot(string id = "", int x = -1, int y = -1);
    virtual ~TrackBot();
    virtual void setLocation(int x, int y) override;
    virtual void actionThink(Battlefield* battlefield) override;
    virtual void actionLook(Battlefield* battlefield, int dx, int dy) override;
    virtual void actionFire(Battlefield* battlefield, int dx, int dy) override;
    virtual void actionMove(Battlefield* battlefield) override;
    virtual void actions(Battlefield* battlefield) override;
    virtual void actionUpgrade(Battlefield* battlefield) override { /* No further upgrade */ }
};

// ====================================================================
// BATTLEFIELD CLASS DECLARATION (Header-like)
// ====================================================================
class Battlefield {
private:
    int BATTLEFIELD_NUM_OF_COLS_ = -1;
    int BATTLEFIELD_NUM_OF_ROWS_ = -1;
    int turns_ = -1;
    int numOfRobots_ = -1;
    vector<Robot*> robots_;
    queue<Robot*> destroyedRobots_;
    queue<Robot*> reentryQueue_;
    vector<vector<string>> battlefield_grid_;

public:
    int BATTLEFIELD_NUM_OF_COLS() const;
    int BATTLEFIELD_NUM_OF_ROWS() const;
    int turns() const;
    int numOfRobots() const;
    vector<Robot*>& getRobots();
    vector<vector<string>>& getBattlefieldGrid();
    queue<Robot*>& getReentryQueue();
    void addDestroyedRobot(Robot* r);
    Robot* getRobotAt(int x, int y);
    void readFile(string filename);
    void placeRobots();
    void displayBattlefield() const;
};

// ====================================================================
// METHOD IMPLEMENTATIONS
// ====================================================================
Robot::Robot(string id, int x, int y) : id_(id), robotPositionX(x), robotPositionY(y) {}
Robot::~Robot() {}
int Robot::x() const { return robotPositionX; }
void Robot::setX(int x) { robotPositionX = x; }
int Robot::y() const { return robotPositionY; }
void Robot::setY(int y) { robotPositionY = y; }
string Robot::id() const { return id_; }
void Robot::setId(string id) { id_ = id; }
string Robot::robotType() const { return robotType_; }
void Robot::setRobotType(string robotType) { robotType_ = robotType; }
string Robot::robotName() const { return robotName_; }
void Robot::setRobotName(string robotName) { robotName_ = robotName; }
int Robot::numOfLives() const { return numOfLives_; }
void Robot::setNumOfLives(int numOfLives) { numOfLives_ = numOfLives; }
int Robot::numOfKills() const { return numOfKills_; }
void Robot::setNumOfKills(int numOfKills) { numOfKills_ = numOfKills; }
int Robot::getShells() const { return shells_; }
void Robot::setShells(int s) { shells_ = s; }
void Robot::reduceLife() { if (numOfLives_ > 0) numOfLives_--; }
void Robot::incrementKills() { numOfKills_++; }
bool Robot::isAlive() const { return numOfLives_ > 0; }
ostream& operator<<(ostream& out, const Robot& r) {
    out << r.id_ << " at (" << r.robotPositionX << ", " << r.robotPositionY << ")";
    return out;
}

GenericRobot::GenericRobot(string id, int x, int y) : Robot(id, x, y) {
    robotType_ = "GenericRobot";
    shells_ = 10;
    numOfLives_ = 3;
    upgradeStage_ = 0;
    upgradedAreas_ = {false, false, false};
    reentryAttempts_ = 0;
}
GenericRobot::~GenericRobot() {}
void GenericRobot::setLocation(int x, int y) { robotPositionX = x; robotPositionY = y; }
void GenericRobot::actionThink(Battlefield* battlefield) {
    cout << robotName_ << " (" << id_ << ") is thinking..." << endl;
    logFile << robotName_ << " (" << id_ << ") is thinking..." << endl;
}
void GenericRobot::actionLook(Battlefield* battlefield, int dx, int dy) {
    cout << robotName_ << " (" << id_ << ") looks at (" << robotPositionX + dx << ", " << robotPositionY + dy << ")" << endl;
    logFile << robotName_ << " (" << id_ << ") looks at (" << robotPositionX + dx << ", " << robotPositionY + dy << ")" << endl;
}
void GenericRobot::actionFire(Battlefield* battlefield, int dx, int dy) {
    if (shells_ <= 0) {
        cout << robotName_ << " (" << id_ << ") has no shells! Self-destructs!" << endl;
        logFile << robotName_ << " (" << id_ << ") has no shells! Self-destructs!" << endl;
        numOfLives_ = 0;
        battlefield->getBattlefieldGrid()[robotPositionY][robotPositionX] = "*";
        battlefield->addDestroyedRobot(this);
        return;
    }
    shells_--;
    if (dx == 0 && dy == 0) {
        cout << robotName_ << " (" << id_ << ") cannot fire at itself" << endl;
        logFile << robotName_ << " (" << id_ << ") cannot fire at itself" << endl;
        return;
    }
    int targetX = robotPositionX + dx;
    int targetY = robotPositionY + dy;
    if (targetY >= 0 && targetY < battlefield->BATTLEFIELD_NUM_OF_ROWS() && targetX >= 0 && targetX < battlefield->BATTLEFIELD_NUM_OF_COLS()) {
        string targetContent = battlefield->getBattlefieldGrid()[targetY][targetX];
        if (targetContent != "*") {
            Robot* targetRobot = battlefield->getRobotAt(targetX, targetY);
            if (targetRobot && targetRobot->id() != id_) {
                if (targetRobot->robotType() == "HideBot" && targetRobot->isHidden()) {
                    cout << "  " << id_ << " fired at " << targetRobot->id() << " but it's hidden! Miss!" << endl;
                    logFile << "  " << id_ << " fired at " << targetRobot->id() << " but it's hidden! Miss!" << endl;
                    return;
                }
                if (rand() % 100 < 70) {
                    cout << "  ONE-SHOT KILL! " << id_ << " instantly destroyed " << targetRobot->id() << "!" << endl;
                    logFile << "  ONE-SHOT KILL! " << id_ << " instantly destroyed " << targetRobot->id() << "!" << endl;
                    targetRobot->setNumOfLives(0);
                    if (!targetRobot->isAlive()) {
                        battlefield->getBattlefieldGrid()[targetY][targetX] = "*";
                        battlefield->addDestroyedRobot(targetRobot);
                        incrementKills();
                    }
                } else {
                    cout << "  MISS! " << id_ << " missed target" << endl;
                    logFile << "  MISS! " << id_ << " missed target" << endl;
                }
            } else {
                cout << "  Shot hit empty space or self" << endl;
                logFile << "  Shot hit empty space or self" << endl;
            }
        } else {
            cout << "  Shot hit empty space" << endl;
            logFile << "  Shot hit empty space" << endl;
        }
    } else {
        cout << "  Shot out of bounds" << endl;
        logFile << "  Shot out of bounds" << endl;
    }
}
void GenericRobot::actionMove(Battlefield* battlefield) {
    int moves[9][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,0},{0,1},{1,-1},{1,0},{1,1}};
    int moveIndex = rand()%9; int dx=moves[moveIndex][1]; int dy=moves[moveIndex][0];
    int newX=robotPositionX+dx; int newY=robotPositionY+dy;
    if (newY >=0 && newY < battlefield->BATTLEFIELD_NUM_OF_ROWS() && newX >=0 && newX < battlefield->BATTLEFIELD_NUM_OF_COLS()) {
        if (battlefield->getBattlefieldGrid()[newY][newX] == "*") {
            battlefield->getBattlefieldGrid()[robotPositionY][robotPositionX] = "*";
            setX(newX); setY(newY);
            battlefield->getBattlefieldGrid()[newY][newX] = id_;
            cout << "  " << id_ << " moved to (" << newX << ", " << newY << ")" << endl;
            logFile << "  " << id_ << " moved to (" << newX << ", " << newY << ")" << endl;
        } else {
            cout << "  " << id_ << " can't move - space occupied" << endl;
            logFile << "  " << id_ << " can't move - space occupied" << endl;
        }
    } else {
        cout << "  " << id_ << " can't move - out of bounds" << endl;
        logFile << "  " << id_ << " can't move - out of bounds" << endl;
    }
}
void GenericRobot::actionUpgrade(Battlefield* battlefield) {
    if (numOfKills_ >= 1 && upgradeStage_ < 3) {
        cout << "\nUPGRADE INITIATED for " << robotName_ << " (" << id_ << ") due to a kill!" << endl;
        logFile << "\nUPGRADE INITIATED for " << robotName_ << " (" << id_ << ") due to a kill!" << endl;
        vector<int> availableAreas;
        if (!upgradedAreas_[0]) availableAreas.push_back(0);
        if (!upgradedAreas_[1]) availableAreas.push_back(1);
        if (!upgradedAreas_[2]) availableAreas.push_back(2);
        if (availableAreas.empty()) {
            cout << "  No more upgrade areas available for " << robotName_ << " (" << id_ << ")." << endl;
            logFile << "  No more upgrade areas available for " << robotName_ << " (" << id_ << ")." << endl;
            return;
        }
        int chosenAreaIndex = availableAreas[rand()%availableAreas.size()];
        string areaName; Robot* newRobot = nullptr;
        int cX=robotPositionX; int cY=robotPositionY; string cId=id_; string cName=robotName_;
        int cKills=numOfKills_; int cShells=shells_; int cLives=numOfLives_;
        vector<bool> cUpgradedAreas = upgradedAreas_; int cUpgradeStage = upgradeStage_; int cReentryAttempts = reentryAttempts_;
        cUpgradedAreas[chosenAreaIndex] = true; cUpgradeStage++;
        battlefield->getBattlefieldGrid()[cY][cX] = "*";
        if (chosenAreaIndex == 0) { areaName = "Moving"; int choice = rand()%2; if (choice == 0) newRobot = new HideBot(cId,cX,cY); else newRobot = new JumpBot(cId,cX,cY); }
        else if (chosenAreaIndex == 1) { areaName = "Shooting"; int choice = rand()%3; if (choice == 0) newRobot = new LongShotBot(cId,cX,cY); else if (choice == 1) newRobot = new SemiAutoBot(cId,cX,cY); else newRobot = new ThirtyShotBot(cId,cX,cY); }
        else { areaName = "Seeing"; int choice = rand()%2; if (choice == 0) newRobot = new ScoutBot(cId,cX,cY); else newRobot = new TrackBot(cId,cX,cY); }
        newRobot->setRobotName(cName); newRobot->setNumOfKills(cKills); newRobot->setShells(cShells); newRobot->setNumOfLives(max(cLives, newRobot->numOfLives()));
        newRobot->setUpgradeStage(cUpgradeStage); newRobot->setUpgradedAreas(cUpgradedAreas); newRobot->setReentryAttempts(cReentryAttempts);

        // Recover shells upon upgrade
        newRobot->setShells(10); // Reset to default shell count

        cout << robotName_ << " (" << id_ << ") has transformed into a " << newRobot->robotType() << " (" << newRobot->robotName() << ") from " << areaName << " upgrade!" << endl;
        logFile << robotName_ << " (" << id_ << ") has transformed into a " << newRobot->robotType() << " (" << newRobot->robotName() << ") from " << areaName << " upgrade!" << endl;
        for (size_t i=0; i < battlefield->getRobots().size(); ++i) {
            if (battlefield->getRobots()[i] == this) { delete battlefield->getRobots()[i]; battlefield->getRobots()[i] = newRobot; break; }
        }
        battlefield->getBattlefieldGrid()[cY][cX] = newRobot->id();
    } else if (numOfKills_ < 1) {
        cout << "  " << robotName_ << " (" << id_ << ") needs at least 1 kill to upgrade." << endl;
        logFile << "  " << robotName_ << " (" << id_ << ") needs at least 1 kill to upgrade." << endl;
    } else {
        cout << "  " << robotName_ << " (" << id_ << ") has reached maximum upgrades." << endl;
        logFile << "  " << robotName_ << " (" << id_ << ") has reached maximum upgrades." << endl;
    }
}
void GenericRobot::actions(Battlefield* battlefield) {
    int offs[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
    actionThink(battlefield);
    int ldx=(rand()%3)-1; int ldy=(rand()%3)-1; actionLook(battlefield, ldx, ldy);
    int fi=rand()%8; int fdx=offs[fi][1]; int fdy=offs[fi][0]; actionFire(battlefield, fdx, fdy);
    actionMove(battlefield);
    actionUpgrade(battlefield);
}

HideBot::HideBot(string id, int x, int y) : Robot(id,x,y) { robotType_="HideBot"; robotName_="Ghost"; numOfLives_=3; shells_=10; hideUses_=3; }
HideBot::~HideBot() {}
void HideBot::setLocation(int x, int y) { robotPositionX = x; robotPositionY = y; }
void HideBot::actionThink(Battlefield* battlefield) {
    cout << robotName_ << " (" << id_ << ") [HIDEBOT] is thinking... (considering hiding)" << endl;
    logFile << robotName_ << " (" << id_ << ") [HIDEBOT] is thinking... (considering hiding)" << endl;
}
void HideBot::actionLook(Battlefield* battlefield, int dx, int dy) {
    cout << robotName_ << " (" << id_ << ") [HIDEBOT] peeks at (" << robotPositionX+dx << ", " << robotPositionY+dy << ")" << endl;
    logFile << robotName_ << " (" << id_ << ") [HIDEBOT] peeks at (" << robotPositionX+dx << ", " << robotPositionY+dy << ")" << endl;
}
void HideBot::actionFire(Battlefield* battlefield, int dx, int dy) {
    if (shells_ <= 0) {
        cout << robotName_ << " (" << id_ << ") [HIDEBOT] is out of ammo! Seeking cover." << endl;
        logFile << robotName_ << " (" << id_ << ") [HIDEBOT] is out of ammo! Seeking cover." << endl;
        return;
    }
    shells_--;
    if (dx==0 && dy==0) {
        cout << robotName_ << " (" << id_ << ") [HIDEBOT] cannot fire at itself." << endl;
        logFile << robotName_ << " (" << id_ << ") [HIDEBOT] cannot fire at itself." << endl;
        return;
    }
    int tX=robotPositionX+dx; int tY=robotPositionY+dy;
    if (tY>=0 && tY<battlefield->BATTLEFIELD_NUM_OF_ROWS() && tX>=0 && tX<battlefield->BATTLEFIELD_NUM_OF_COLS()) {
        string tc=battlefield->getBattlefieldGrid()[tY][tX];
        if (tc!="*") {
            Robot* tr=battlefield->getRobotAt(tX,tY);
            if (tr && tr->id()!=id_) {
                if (tr->robotType()=="HideBot" && tr->isHidden()) {
                    cout << "  " << id_ << " fired at " << tr->id() << " but it's hidden! Miss!" << endl;
                    logFile << "  " << id_ << " fired at " << tr->id() << " but it's hidden! Miss!" << endl;
                    return;
                }
                if (rand()%100 < 70) {
                    cout << "  HIDEBOT HIT! " << id_ << " hit " << tr->id() << endl;
                    logFile << "  HIDEBOT HIT! " << id_ << " hit " << tr->id() << endl;
                    tr->reduceLife();
                    if (!tr->isAlive()) { battlefield->getBattlefieldGrid()[tY][tX]="*"; battlefield->addDestroyedRobot(tr); incrementKills(); }
                } else {
                    cout << "  HIDEBOT MISSED! " << id_ << " shot wide." << endl;
                    logFile << "  HIDEBOT MISSED! " << id_ << " shot wide." << endl;
                }
            }
        } else {
            cout << "  HIDEBOT shot hit empty space." << endl;
            logFile << "  HIDEBOT shot hit empty space." << endl;
        }
    } else {
        cout << "  HIDEBOT shot out of bounds." << endl;
        logFile << "  HIDEBOT shot out of bounds." << endl;
    }
}
void HideBot::actionMove(Battlefield* battlefield) {
    if (isHidden_) {
        setHidden(false); setHideDuration(0);
        battlefield->getBattlefieldGrid()[robotPositionY][robotPositionX] = id_;
        cout << "  " << id_ << " [HIDEBOT] unhides at (" << robotPositionX << ", " << robotPositionY << ")." << endl;
        logFile << "  " << id_ << " [HIDEBOT] unhides at (" << robotPositionX << ", " << robotPositionY << ")." << endl;
    }
    if (hideUses_ > 0 && rand()%2==0) {
        setHidden(true); setHideDuration(1); hideUses_--;
        battlefield->getBattlefieldGrid()[robotPositionY][robotPositionX] = "*";
        cout << "  " << id_ << " [HIDEBOT] hides! Remaining hides: " << hideUses_ << endl;
        logFile << "  " << id_ << " [HIDEBOT] hides! Remaining hides: " << hideUses_ << endl;
        return;
    }
    int mvs[9][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,0},{0,1},{1,-1},{1,0},{1,1}};
    int mi=rand()%9; int dx=mvs[mi][1]; int dy=mvs[mi][0];
    int nX=robotPositionX+dx; int nY=robotPositionY+dy;
    if (nY>=0 && nY<battlefield->BATTLEFIELD_NUM_OF_ROWS() && nX>=0 && nX<battlefield->BATTLEFIELD_NUM_OF_COLS()) {
        if (battlefield->getBattlefieldGrid()[nY][nX]=="*") {
            battlefield->getBattlefieldGrid()[robotPositionY][robotPositionX]="*";
            setX(nX); setY(nY); battlefield->getBattlefieldGrid()[nY][nX]=id_;
            cout << "  " << id_ << " [HIDEBOT] moved to (" << nX << ", " << nY << ")" << endl;
            logFile << "  " << id_ << " [HIDEBOT] moved to (" << nX << ", " << nY << ")" << endl;
        } else {
            cout << "  " << id_ << " [HIDEBOT] can't move - space occupied." << endl;
            logFile << "  " << id_ << " [HIDEBOT] can't move - space occupied." << endl;
        }
    } else {
        cout << "  " << id_ << " [HIDEBOT] can't move - out of bounds." << endl;
        logFile << "  " << id_ << " [HIDEBOT] can't move - out of bounds." << endl;
    }
}
void HideBot::actions(Battlefield* battlefield) {
    int offs[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
    actionThink(battlefield);
    int ldx=(rand()%3)-1; int ldy=(rand()%3)-1; actionLook(battlefield,ldx,ldy);
    int fi=rand()%8; int fdx=offs[fi][1]; int fdy=offs[fi][0]; actionFire(battlefield,fdx,fdy);
    actionMove(battlefield);
}

JumpBot::JumpBot(string id, int x, int y) : Robot(id,x,y) { robotType_="JumpBot"; robotName_="Skippy"; numOfLives_=3; shells_=10; jumpUses_=3; }
JumpBot::~JumpBot() {}
void JumpBot::setLocation(int x, int y) { robotPositionX = x; robotPositionY = y; }
void JumpBot::actionThink(Battlefield* battlefield) {
    cout << robotName_ << " (" << id_ << ") [JUMPBOT] is thinking... (looking for jump spots)" << endl;
    logFile << robotName_ << " (" << id_ << ") [JUMPBOT] is thinking... (looking for jump spots)" << endl;
}
void JumpBot::actionLook(Battlefield* battlefield, int dx, int dy) {
    cout << robotName_ << " (" << id_ << ") [JUMPBOT] scans area at (" << robotPositionX+dx << ", " << robotPositionY+dy << ")" << endl;
    logFile << robotName_ << " (" << id_ << ") [JUMPBOT] scans area at (" << robotPositionX+dx << ", " << robotPositionY+dy << ")" << endl;
}
void JumpBot::actionFire(Battlefield* battlefield, int dx, int dy) {
    if (shells_ <= 0) {
        cout << robotName_ << " (" << id_ << ") [JUMPBOT] is out of ammo! Seeking cover." << endl;
        logFile << robotName_ << " (" << id_ << ") [JUMPBOT] is out of ammo! Seeking cover." << endl;
        return;
    }
    shells_--;
    if (dx==0 && dy==0) {
        cout << robotName_ << " (" << id_ << ") [JUMPBOT] cannot fire at itself." << endl;
        logFile << robotName_ << " (" << id_ << ") [JUMPBOT] cannot fire at itself." << endl;
        return;
    }
    int tX=robotPositionX+dx; int tY=robotPositionY+dy;
    if (tY>=0 && tY<battlefield->BATTLEFIELD_NUM_OF_ROWS() && tX>=0 && tX<battlefield->BATTLEFIELD_NUM_OF_COLS()) {
        string tc=battlefield->getBattlefieldGrid()[tY][tX];
        if (tc!="*") {
            Robot* tr=battlefield->getRobotAt(tX,tY);
            if (tr && tr->id()!=id_) {
                if (tr->robotType()=="HideBot" && tr->isHidden()) {
                    cout << "  " << id_ << " fired at " << tr->id() << " but it's hidden! Miss!" << endl;
                    logFile << "  " << id_ << " fired at " << tr->id() << " but it's hidden! Miss!" << endl;
                    return;
                }
                if (rand()%100 < 70) {
                    cout << "  JUMPBOT HIT! " << id_ << " hit " << tr->id() << endl;
                    logFile << "  JUMPBOT HIT! " << id_ << " hit " << tr->id() << endl;
                    tr->reduceLife();
                    if (!tr->isAlive()) { battlefield->getBattlefieldGrid()[tY][tX]="*"; battlefield->addDestroyedRobot(tr); incrementKills(); }
                } else {
                    cout << "  JUMPBOT MISSED! " << id_ << " shot wide." << endl;
                    logFile << "  JUMPBOT MISSED! " << id_ << " shot wide." << endl;
                }
            }
        } else {
            cout << "  JUMPBOT shot hit empty space." << endl;
            logFile << "  JUMPBOT shot hit empty space." << endl;
        }
    } else {
        cout << "  JUMPBOT shot out of bounds." << endl;
        logFile << "  JUMPBOT shot out of bounds." << endl;
    }
}
void JumpBot::actionMove(Battlefield* battlefield) {
    if (jumpUses_ > 0 && rand()%2==0) {
        int nX, nY; bool found=false; int maxAtt=battlefield->BATTLEFIELD_NUM_OF_ROWS()*battlefield->BATTLEFIELD_NUM_OF_COLS()*2; int att=0;
        do { nX=rand()%battlefield->BATTLEFIELD_NUM_OF_COLS(); nY=rand()%battlefield->BATTLEFIELD_NUM_OF_ROWS(); if(battlefield->getBattlefieldGrid()[nY][nX]=="*") found=true; att++; } while(!found && att<maxAtt);
        if (found) {
            battlefield->getBattlefieldGrid()[robotPositionY][robotPositionX]="*"; setX(nX); setY(nY); battlefield->getBattlefieldGrid()[nY][nX]=id_; jumpUses_--;
            cout << "  " << id_ << " [JUMPBOT] jumped to (" << nX << ", " << nY << ")! Remaining jumps: " << jumpUses_ << endl;
            logFile << "  " << id_ << " [JUMPBOT] jumped to (" << nX << ", " << nY << ")! Remaining jumps: " << jumpUses_ << endl;
            return;
        } else {
            cout << "  " << id_ << " [JUMPBOT] tried to jump but no empty spot found." << endl;
            logFile << "  " << id_ << " [JUMPBOT] tried to jump but no empty spot found." << endl;
        }
    }
    int mvs[9][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,0},{0,1},{1,-1},{1,0},{1,1}};
    int mi=rand()%9; int dx=mvs[mi][1]; int dy=mvs[mi][0];
    int nX=robotPositionX+dx; int nY=robotPositionY+dy;
    if (nY>=0 && nY<battlefield->BATTLEFIELD_NUM_OF_ROWS() && nX>=0 && nX<battlefield->BATTLEFIELD_NUM_OF_COLS()) {
        if (battlefield->getBattlefieldGrid()[nY][nX]=="*") {
            battlefield->getBattlefieldGrid()[robotPositionY][robotPositionX]="*"; setX(nX); setY(nY); battlefield->getBattlefieldGrid()[nY][nX]=id_;
            cout << "  " << id_ << " [JUMPBOT] moved to (" << nX << ", " << nY << ")" << endl;
            logFile << "  " << id_ << " [JUMPBOT] moved to (" << nX << ", " << nY << ")" << endl;
        } else {
            cout << "  " << id_ << " [JUMPBOT] can't move - space occupied." << endl;
            logFile << "  " << id_ << " [JUMPBOT] can't move - space occupied." << endl;
        }
    } else {
        cout << "  " << id_ << " [JUMPBOT] can't move - out of bounds." << endl;
        logFile << "  " << id_ << " [JUMPBOT] can't move - out of bounds." << endl;
    }
}
void JumpBot::actions(Battlefield* battlefield) {
    int offs[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
    actionThink(battlefield);
    int ldx=(rand()%3)-1; int ldy=(rand()%3)-1; actionLook(battlefield,ldx,ldy);
    int fi=rand()%8; int fdx=offs[fi][1]; int fdy=offs[fi][0]; actionFire(battlefield,fdx,fdy);
    actionMove(battlefield);
}

LongShotBot::LongShotBot(string id, int x, int y):Robot(id,x,y){robotType_="LongShotBot";robotName_="Sniper";numOfLives_=3;shells_=10;}
LongShotBot::~LongShotBot(){}
void LongShotBot::setLocation(int x,int y){robotPositionX=x;robotPositionY=y;}
void LongShotBot::actionThink(Battlefield* battlefield){
    cout << robotName_ << " (" << id_ << ") [LONGSHOTBOT] is thinking... (lining up a long shot)" << endl;
    logFile << robotName_ << " (" << id_ << ") [LONGSHOTBOT] is thinking... (lining up a long shot)" << endl;
}
void LongShotBot::actionLook(Battlefield* battlefield, int dx, int dy){
    cout << robotName_ << " (" << id_ << ") [LONGSHOTBOT] scopes out (" << robotPositionX+dx << ", " << robotPositionY+dy << ")" << endl;
    logFile << robotName_ << " (" << id_ << ") [LONGSHOTBOT] scopes out (" << robotPositionX+dx << ", " << robotPositionY+dy << ")" << endl;
}
void LongShotBot::actionFire(Battlefield* battlefield, int dx, int dy){
    if(shells_<=0){
        cout << robotName_ << " (" << id_ << ") [LONGSHOTBOT] is out of ammo! Reloading!" << endl;
        logFile << robotName_ << " (" << id_ << ") [LONGSHOTBOT] is out of ammo! Reloading!" << endl;
        return;
    }
    shells_--;
    if(dx==0 && dy==0){
        cout << robotName_ << " (" << id_ << ") [LONGSHOTBOT] cannot fire at itself." << endl;
        logFile << robotName_ << " (" << id_ << ") [LONGSHOTBOT] cannot fire at itself." << endl;
        return;
    }
    if(abs(dx)+abs(dy)>3){
        cout << "  " << id_ << " [LONGSHOTBOT] cannot fire that far (max range 3 units)." << endl;
        logFile << "  " << id_ << " [LONGSHOTBOT] cannot fire that far (max range 3 units)." << endl;
        return;
    }
    int tX=robotPositionX+dx; int tY=robotPositionY+dy;
    if(tY>=0 && tY<battlefield->BATTLEFIELD_NUM_OF_ROWS() && tX>=0 && tX<battlefield->BATTLEFIELD_NUM_OF_COLS()){
        string tc=battlefield->getBattlefieldGrid()[tY][tX];
        if(tc!="*"){
            Robot* tr=battlefield->getRobotAt(tX,tY);
            if(tr && tr->id()!=id_){
                if(tr->robotType()=="HideBot" && tr->isHidden()){
                    cout << "  " << id_ << " fired at " << tr->id() << " but it's hidden! Miss!" << endl;
                    logFile << "  " << id_ << " fired at " << tr->id() << " but it's hidden! Miss!" << endl;
                    return;
                }
                if(rand()%100 < 70){
                    cout << "  LONGSHOT HIT! " << id_ << " hit " << tr->id() << " from afar!" << endl;
                    logFile << "  LONGSHOT HIT! " << id_ << " hit " << tr->id() << " from afar!" << endl;
                    tr->reduceLife();
                    if(!tr->isAlive()){battlefield->getBattlefieldGrid()[tY][tX]="*";battlefield->addDestroyedRobot(tr);incrementKills();}
                } else {
                    cout << "  LONGSHOT MISSED! " << id_ << " shot wide." << endl;
                    logFile << "  LONGSHOT MISSED! " << id_ << " shot wide." << endl;
                }
            }
        } else {
            cout << "  LONGSHOT shot hit empty space." << endl;
            logFile << "  LONGSHOT shot hit empty space." << endl;
        }
    } else {
        cout << "  LONGSHOT shot out of bounds." << endl;
        logFile << "  LONGSHOT shot out of bounds." << endl;
    }
}
void LongShotBot::actionMove(Battlefield* battlefield){
    int mvs[9][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,0},{0,1},{1,-1},{1,0},{1,1}};
    int mi=rand()%9; int dx=mvs[mi][1]; int dy=mvs[mi][0];
    int nX=robotPositionX+dx; int nY=robotPositionY+dy;
    if(nY>=0 && nY<battlefield->BATTLEFIELD_NUM_OF_ROWS() && nX>=0 && nX<battlefield->BATTLEFIELD_NUM_OF_COLS()){
        if(battlefield->getBattlefieldGrid()[nY][nX]=="*"){
            battlefield->getBattlefieldGrid()[robotPositionY][robotPositionX]="*"; setX(nX);setY(nY); battlefield->getBattlefieldGrid()[nY][nX]=id_;
            cout << "  " << id_ << " [LONGSHOTBOT] moved to (" << nX << ", " << nY << ")" << endl;
            logFile << "  " << id_ << " [LONGSHOTBOT] moved to (" << nX << ", " << nY << ")" << endl;
        } else {
            cout << "  " << id_ << " [LONGSHOTBOT] can't move - space occupied." << endl;
            logFile << "  " << id_ << " [LONGSHOTBOT] can't move - space occupied." << endl;
        }
    } else {
        cout << "  " << id_ << " [LONGSHOTBOT] can't move - out of bounds." << endl;
        logFile << "  " << id_ << " [LONGSHOTBOT] can't move - out of bounds." << endl;
    }
}
void LongShotBot::actions(Battlefield* battlefield){
    actionThink(battlefield);
    int ldx=(rand()%7)-3; int ldy=(rand()%7)-3; actionLook(battlefield,ldx,ldy);
    int fdx, fdy; do{fdx=(rand()%7)-3; fdy=(rand()%7)-3;}while((abs(fdx)+abs(fdy)>3)||(fdx==0&&fdy==0));
    actionFire(battlefield,fdx,fdy);
    actionMove(battlefield);
}

SemiAutoBot::SemiAutoBot(string id, int x, int y):Robot(id,x,y){robotType_="SemiAutoBot";robotName_="RapidFire";numOfLives_=3;shells_=10;}
SemiAutoBot::~SemiAutoBot(){}
void SemiAutoBot::setLocation(int x,int y){robotPositionX=x;robotPositionY=y;}
void SemiAutoBot::actionThink(Battlefield* battlefield){
    cout << robotName_ << " (" << id_ << ") [SEMIAUTOBOT] is thinking... (preparing a burst)" << endl;
    logFile << robotName_ << " (" << id_ << ") [SEMIAUTOBOT] is thinking... (preparing a burst)" << endl;
}
void SemiAutoBot::actionLook(Battlefield* battlefield, int dx, int dy){
    cout << robotName_ << " (" << id_ << ") [SEMIAUTOBOT] surveys (" << robotPositionX+dx << ", " << robotPositionY+dy << ")" << endl;
    logFile << robotName_ << " (" << id_ << ") [SEMIAUTOBOT] surveys (" << robotPositionX+dx << ", " << robotPositionY+dy << ")" << endl;
}
void SemiAutoBot::actionFire(Battlefield* battlefield, int dx, int dy){
    if(shells_<=0){
        cout << robotName_ << " (" << id_ << ") [SEMIAUTOBOT] is out of ammo! Needs more shells!" << endl;
        logFile << robotName_ << " (" << id_ << ") [SEMIAUTOBOT] is out of ammo! Needs more shells!" << endl;
        return;
    }
    shells_--;
    if(dx==0 && dy==0){
        cout << robotName_ << " (" << id_ << ") [SEMIAUTOBOT] cannot fire at itself." << endl;
        logFile << robotName_ << " (" << id_ << ") [SEMIAUTOBOT] cannot fire at itself." << endl;
        return;
    }
    int tX=robotPositionX+dx; int tY=robotPositionY+dy;
    if(tY>=0 && tY<battlefield->BATTLEFIELD_NUM_OF_ROWS() && tX>=0 && tX<battlefield->BATTLEFIELD_NUM_OF_COLS()){
        string tc=battlefield->getBattlefieldGrid()[tY][tX];
        if(tc!="*"){
            Robot* tr=battlefield->getRobotAt(tX,tY);
            if(tr && tr->id()!=id_){
                if(tr->robotType()=="HideBot" && tr->isHidden()){
                    cout << "  " << id_ << " fired at " << tr->id() << " but it's hidden! Miss!" << endl;
                    logFile << "  " << id_ << " fired at " << tr->id() << " but it's hidden! Miss!" << endl;
                    return;
                }
                cout << "  " << id_ << " [SEMIAUTOBOT] fires 3 consecutive shots at " << tr->id() << "!" << endl;
                logFile << "  " << id_ << " [SEMIAUTOBOT] fires 3 consecutive shots at " << tr->id() << "!" << endl;
                for(int i=0; i<3; ++i){
                    if(tr->isAlive()){
                        if(rand()%100 < 70){
                            cout << "    Shot " << (i+1) << ": HIT! " << tr->id() << " takes damage." << endl;
                            logFile << "    Shot " << (i+1) << ": HIT! " << tr->id() << " takes damage." << endl;
                            tr->reduceLife();
                            if(!tr->isAlive()){
                                cout << "    Shot " << (i+1) << ": " << tr->id() << " destroyed!" << endl;
                                logFile << "    Shot " << (i+1) << ": " << tr->id() << " destroyed!" << endl;
                                battlefield->getBattlefieldGrid()[tY][tX]="*";battlefield->addDestroyedRobot(tr);incrementKills(); break;
                            }
                        } else {
                            cout << "    Shot " << (i+1) << ": MISSED!" << endl;
                            logFile << "    Shot " << (i+1) << ": MISSED!" << endl;
                        }
                    } else {
                        cout << "    Target " << tr->id() << " already destroyed." << endl;
                        logFile << "    Target " << tr->id() << " already destroyed." << endl;
                        break;
                    }
                }
            }
        } else {
            cout << "  SEMIAUTOBOT shot hit empty space." << endl;
            logFile << "  SEMIAUTOBOT shot hit empty space." << endl;
        }
    } else {
        cout << "  SEMIAUTOBOT shot out of bounds." << endl;
        logFile << "  SEMIAUTOBOT shot out of bounds." << endl;
    }
}
void SemiAutoBot::actionMove(Battlefield* battlefield){
    int mvs[9][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,0},{0,1},{1,-1},{1,0},{1,1}};
    int mi=rand()%9; int dx=mvs[mi][1]; int dy=mvs[mi][0];
    int nX=robotPositionX+dx; int nY=robotPositionY+dy;
    if(nY>=0 && nY<battlefield->BATTLEFIELD_NUM_OF_ROWS() && nX>=0 && nX<battlefield->BATTLEFIELD_NUM_OF_COLS()){
        if(battlefield->getBattlefieldGrid()[nY][nX]=="*"){
            battlefield->getBattlefieldGrid()[robotPositionY][robotPositionX]="*"; setX(nX);setY(nY); battlefield->getBattlefieldGrid()[nY][nX]=id_;
            cout << "  " << id_ << " [SEMIAUTOBOT] moved to (" << nX << ", " << nY << ")" << endl;
            logFile << "  " << id_ << " [SEMIAUTOBOT] moved to (" << nX << ", " << nY << ")" << endl;
        } else {
            cout << "  " << id_ << " [SEMIAUTOBOT] can't move - space occupied." << endl;
            logFile << "  " << id_ << " [SEMIAUTOBOT] can't move - space occupied." << endl;
        }
    } else {
        cout << "  " << id_ << " [SEMIAUTOBOT] can't move - out of bounds." << endl;
        logFile << "  " << id_ << " [SEMIAUTOBOT] can't move - out of bounds." << endl;
    }
}
void SemiAutoBot::actions(Battlefield* battlefield){
    int offs[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
    actionThink(battlefield);
    int ldx=(rand()%3)-1; int ldy=(rand()%3)-1; actionLook(battlefield,ldx,ldy);
    int fi=rand()%8; int fdx=offs[fi][1]; int fdy=offs[fi][0]; actionFire(battlefield,fdx,fdy);
    actionMove(battlefield);
}

ThirtyShotBot::ThirtyShotBot(string id, int x, int y):Robot(id,x,y){robotType_="ThirtyShotBot";robotName_="AmmoKing";numOfLives_=3;shells_=30;}
ThirtyShotBot::~ThirtyShotBot(){}
void ThirtyShotBot::setLocation(int x,int y){robotPositionX=x;robotPositionY=y;}
void ThirtyShotBot::actionThink(Battlefield* battlefield){
    cout << robotName_ << " (" << id_ << ") [THIRTYSHOTBOT] is thinking... (planning a barrage)" << endl;
    logFile << robotName_ << " (" << id_ << ") [THIRTYSHOTBOT] is thinking... (planning a barrage)" << endl;
}
void ThirtyShotBot::actionLook(Battlefield* battlefield, int dx, int dy){
    cout << robotName_ << " (" << id_ << ") [THIRTYSHOTBOT] observes (" << robotPositionX+dx << ", " << robotPositionY+dy << ")" << endl;
    logFile << robotName_ << " (" << id_ << ") [THIRTYSHOTBOT] observes (" << robotPositionX+dx << ", " << robotPositionY+dy << ")" << endl;
}
void ThirtyShotBot::actionFire(Battlefield* battlefield, int dx, int dy){
    if(shells_<=0){
        cout << robotName_ << " (" << id_ << ") [THIRTYSHOTBOT] is out of ammo! Self-destructs!" << endl;
        logFile << robotName_ << " (" << id_ << ") [THIRTYSHOTBOT] is out of ammo! Self-destructs!" << endl;
        numOfLives_=0; battlefield->getBattlefieldGrid()[robotPositionY][robotPositionX]="*"; battlefield->addDestroyedRobot(this); return;
    }
    shells_--;
    if(dx==0 && dy==0){
        cout << robotName_ << " (" << id_ << ") [THIRTYSHOTBOT] cannot fire at itself." << endl;
        logFile << robotName_ << " (" << id_ << ") [THIRTYSHOTBOT] cannot fire at itself." << endl;
        return;
    }
    int tX=robotPositionX+dx; int tY=robotPositionY+dy;
    if(tY>=0 && tY<battlefield->BATTLEFIELD_NUM_OF_ROWS() && tX>=0 && tX<battlefield->BATTLEFIELD_NUM_OF_COLS()){
        string tc=battlefield->getBattlefieldGrid()[tY][tX];
        if(tc!="*"){
            Robot* tr=battlefield->getRobotAt(tX,tY);
            if(tr && tr->id()!=id_){
                if(tr->robotType()=="HideBot" && tr->isHidden()){
                    cout << "  " << id_ << " fired at " << tr->id() << " but it's hidden! Miss!" << endl;
                    logFile << "  " << id_ << " fired at " << tr->id() << " but it's hidden! Miss!" << endl;
                    return;
                }
                if(rand()%100 < 70){
                    cout << "  THIRTYSHOT HIT! " << id_ << " hit " << tr->id() << endl;
                    logFile << "  " << id_ << " hit " << tr->id() << endl;
                    tr->reduceLife();
                    if(!tr->isAlive()){battlefield->getBattlefieldGrid()[tY][tX]="*";battlefield->addDestroyedRobot(tr);incrementKills();}
                } else {
                    cout << "  THIRTYSHOT MISSED! " << id_ << " shot wide." << endl;
                    logFile << "  " << id_ << " shot wide." << endl;
                }
            }
        } else {
            cout << "  THIRTYSHOT shot hit empty space." << endl;
            logFile << "  THIRTYSHOT shot hit empty space." << endl;
        }
    } else {
        cout << "  THIRTYSHOT shot out of bounds." << endl;
        logFile << "  THIRTYSHOT shot out of bounds." << endl;
    }
}
void ThirtyShotBot::actionMove(Battlefield* battlefield){
    int mvs[9][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,0},{0,1},{1,-1},{1,0},{1,1}};
    int mi=rand()%9; int dx=mvs[mi][1]; int dy=mvs[mi][0];
    int nX=robotPositionX+dx; int nY=robotPositionY+dy;
    if(nY>=0 && nY<battlefield->BATTLEFIELD_NUM_OF_ROWS() && nX>=0 && nX<battlefield->BATTLEFIELD_NUM_OF_COLS()){
        if(battlefield->getBattlefieldGrid()[nY][nX]=="*"){
            battlefield->getBattlefieldGrid()[robotPositionY][robotPositionX]="*"; setX(nX);setY(nY); battlefield->getBattlefieldGrid()[nY][nX]=id_;
            cout << "  " << id_ << " [THIRTYSHOTBOT] moved to (" << nX << ", " << nY << ")" << endl;
            logFile << "  " << id_ << " [THIRTYSHOTBOT] moved to (" << nX << ", " << nY << ")" << endl;
        } else {
            cout << "  " << id_ << " [THIRTYSHOTBOT] can't move - space occupied." << endl;
            logFile << "  " << id_ << " [THIRTYSHOTBOT] can't move - space occupied." << endl;
        }
    } else {
        cout << "  " << id_ << " [THIRTYSHOTBOT] can't move - out of bounds." << endl;
        logFile << "  " << id_ << " [THIRTYSHOTBOT] can't move - out of bounds." << endl;
    }
}
void ThirtyShotBot::actions(Battlefield* battlefield){
    int offs[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
    actionThink(battlefield);
    int ldx=(rand()%3)-1; int ldy=(rand()%3)-1; actionLook(battlefield,ldx,ldy);
    int fi=rand()%8; int fdx=offs[fi][1]; int fdy=offs[fi][0]; actionFire(battlefield,fdx,fdy);
    actionMove(battlefield);
}

ScoutBot::ScoutBot(string id, int x, int y):Robot(id,x,y){robotType_="ScoutBot";robotName_="EagleEye";numOfLives_=2;shells_=15;fullScanUses_=3;}
ScoutBot::~ScoutBot(){}
void ScoutBot::setLocation(int x,int y){robotPositionX=x;robotPositionY=y;}
void ScoutBot::actionThink(Battlefield* battlefield){
    cout << robotName_ << " (" << id_ << ") [SCOUTBOT] is thinking... (considering full scan)" << endl;
    logFile << robotName_ << " (" << id_ << ") [SCOUTBOT] is thinking... (considering full scan)" << endl;
}
void ScoutBot::actionLook(Battlefield* battlefield, int dx, int dy){
    if(fullScanUses_ > 0 && rand()%2==0){
        cout << "  " << id_ << " [SCOUTBOT] performs a full battlefield scan!" << endl;
        logFile << "  " << id_ << " [SCOUTBOT] performs a full battlefield scan!" << endl;
        for(int r=0; r<battlefield->BATTLEFIELD_NUM_OF_ROWS(); ++r){
            for(int c=0; c<battlefield->BATTLEFIELD_NUM_OF_COLS(); ++c){
                string content = battlefield->getBattlefieldGrid()[r][c];
                if(content!="*"){
                    Robot* tr = battlefield->getRobotAt(c,r);
                    if(tr){
                        cout << "    Detected " << tr->robotName() << " (" << tr->id() << ") at (" << c << ", " << r << ")" << endl;
                        logFile << "    Detected " << tr->robotName() << " (" << tr->id() << ") at (" << c << ", " << r << ")" << endl;
                    }
                }
            }
        }
        fullScanUses_--;
        cout << "  Remaining full scans: " << fullScanUses_ << endl;
        logFile << "  Remaining full scans: " << fullScanUses_ << endl;
    } else {
        cout << robotName_ << " (" << id_ << ") [SCOUTBOT] quickly surveys (" << robotPositionX+dx << ", " << robotPositionY+dy << ")" << endl;
        logFile << robotName_ << " (" << id_ << ") [SCOUTBOT] quickly surveys (" << robotPositionX+dx << ", " << robotPositionY+dy << ")" << endl;
    }
}
void ScoutBot::actionFire(Battlefield* battlefield, int dx, int dy){
    if(shells_<=0){
        cout << robotName_ << " (" << id_ << ") [SCOUTBOT] is out of shells! Retreating!" << endl;
        logFile << robotName_ << " (" << id_ << ") [SCOUTBOT] is out of shells! Retreating!" << endl;
        return;
    }
    shells_--;
    if(dx==0 && dy==0){
        cout << robotName_ << " (" << id_ << ") [SCOUTBOT] cannot fire at itself." << endl;
        logFile << robotName_ << " (" << id_ << ") [SCOUTBOT] cannot fire at itself." << endl;
        return;
    }
    int tX=robotPositionX+dx; int tY=robotPositionY+dy;
    if(tY>=0 && tY<battlefield->BATTLEFIELD_NUM_OF_ROWS() && tX>=0 && tX<battlefield->BATTLEFIELD_NUM_OF_COLS()){
        string tc=battlefield->getBattlefieldGrid()[tY][tX];
        if(tc!="*"){
            Robot* tr=battlefield->getRobotAt(tX,tY);
            if(tr && tr->id()!=id_){
                if(tr->robotType()=="HideBot" && tr->isHidden()){
                    cout << "  " << id_ << " fired at " << tr->id() << " but it's hidden! Miss!" << endl;
                    logFile << "  " << id_ << " fired at " << tr->id() << " but it's hidden! Miss!" << endl;
                    return;
                }
                if(rand()%100 < 60){
                    cout << "  SCOUTBOT HIT! " << id_ << " landed a shot on " << tr->id() << endl;
                    logFile << "  SCOUTBOT HIT! " << id_ << " landed a shot on " << tr->id() << endl;
                    tr->reduceLife();
                    if(!tr->isAlive()){battlefield->getBattlefieldGrid()[tY][tX]="*";battlefield->addDestroyedRobot(tr);incrementKills();}
                } else {
                    cout << "  SCOUTBOT MISSED! " << id_ << " shot wide." << endl;
                    logFile << "  SCOUTBOT MISSED! " << id_ << " shot wide." << endl;
                }
            }
        } else {
            cout << "  SCOUTBOT shot hit empty space." << endl;
            logFile << "  SCOUTBOT shot hit empty space." << endl;
        }
    } else {
        cout << "  SCOUTBOT shot out of bounds." << endl;
        logFile << "  SCOUTBOT shot out of bounds." << endl;
    }
}
void ScoutBot::actionMove(Battlefield* battlefield){
    int mvs[24][2]; int k=0;
    for(int dy_m=-2;dy_m<=2;++dy_m)for(int dx_m=-2;dx_m<=2;++dx_m)if(dx_m!=0||dy_m!=0){mvs[k][0]=dy_m;mvs[k][1]=dx_m;k++;}
    int mi=rand()%k; int dx=mvs[mi][1]; int dy=mvs[mi][0];
    int nX=robotPositionX+dx; int nY=robotPositionY+dy;
    if(nY>=0 && nY<battlefield->BATTLEFIELD_NUM_OF_ROWS() && nX>=0 && nX<battlefield->BATTLEFIELD_NUM_OF_COLS()){
        if(battlefield->getBattlefieldGrid()[nY][nX]=="*"){
            battlefield->getBattlefieldGrid()[robotPositionY][robotPositionX]="*"; setX(nX);setY(nY); battlefield->getBattlefieldGrid()[nY][nX]=id_;
            cout << "  " << id_ << " [SCOUTBOT] dashes to (" << nX << ", " << nY << ")" << endl;
            logFile << "  " << id_ << " [SCOUTBOT] dashes to (" << nX << ", " << nY << ")" << endl;
        } else {
            cout << "  " << id_ << " [SCOUTBOT] can't move - space occupied." << endl;
            logFile << "  " << id_ << " [SCOUTBOT] can't move - space occupied." << endl;
        }
    } else {
        cout << "  " << id_ << " [SCOUTBOT] can't move - out of bounds." << endl;
        logFile << "  " << id_ << " [SCOUTBOT] can't move - out of bounds." << endl;
    }
}
void ScoutBot::actions(Battlefield* battlefield){
    int offs[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
    actionThink(battlefield);
    int ldx=(rand()%5)-2; int ldy=(rand()%5)-2; actionLook(battlefield,ldx,ldy);
    int fi=rand()%8; int fdx=offs[fi][1]; int fdy=offs[fi][0]; actionFire(battlefield,fdx,fdy);
    actionMove(battlefield);
}

TrackBot::TrackBot(string id, int x, int y):Robot(id,x,y){robotType_="TrackBot";robotName_="Hunter";numOfLives_=3;shells_=10;trackerCount_=3;}
TrackBot::~TrackBot(){}
void TrackBot::setLocation(int x,int y){robotPositionX=x;robotPositionY=y;}
void TrackBot::actionThink(Battlefield* battlefield){
    cout << robotName_ << " (" << id_ << ") [TRACKBOT] is thinking... (searching for targets to track)" << endl;
    logFile << robotName_ << " (" << id_ << ") [TRACKBOT] is thinking... (searching for targets to track)" << endl;
    if(!trackedRobotId_.empty()){
        Robot* tr=nullptr;
        for(Robot* r : battlefield->getRobots()){ if(r->id()==trackedRobotId_ && r->isAlive()){tr=r;break;}}
        if(tr){
            cout << "  Tracked robot " << tr->id() << " is at (" << tr->x() << ", " << tr->y() << ")" << endl;
            logFile << "  Tracked robot " << tr->id() << " is at (" << tr->x() << ", " << tr->y() << ")" << endl;
        } else {
            cout << "  Tracked robot " << trackedRobotId_ << " is no longer active." << endl;
            logFile << "  Tracked robot " << trackedRobotId_ << " is no longer active." << endl;
            trackedRobotId_="";
        }
    }
}
void TrackBot::actionLook(Battlefield* battlefield, int dx, int dy){
    if(trackerCount_ > 0 && trackedRobotId_.empty()){
        Robot* pt=nullptr; int tX=robotPositionX+dx; int tY=robotPositionY+dy;
        if(tY>=0 && tY<battlefield->BATTLEFIELD_NUM_OF_ROWS() && tX>=0 && tX<battlefield->BATTLEFIELD_NUM_OF_COLS()){pt=battlefield->getRobotAt(tX,tY);}
        if(pt && pt->id()!=id_){
            setTrackedRobotId(pt->id()); decrementTrackerCount();
            cout << "  " << id_ << " [TRACKBOT] planted a tracker on " << pt->id() << "! Remaining trackers: " << trackerCount_ << endl;
            logFile << "  " << id_ << " [TRACKBOT] planted a tracker on " << pt->id() << "! Remaining trackers: " << trackerCount_ << endl;
        } else {
            cout << "  " << id_ << " [TRACKBOT] looked at (" << tX << ", " << tY << ") - no new target to track." << endl;
            logFile << "  " << id_ << " [TRACKBOT] looked at (" << tX << ", " << tY << ") - no new target to track." << endl;
        }
    } else {
        cout << robotName_ << " (" << id_ << ") [TRACKBOT] observes (" << robotPositionX+dx << ", " << robotPositionY+dy << ")" << endl;
        logFile << robotName_ << " (" << id_ << ") [TRACKBOT] observes (" << robotPositionX+dx << ", " << robotPositionY+dy << ")" << endl;
    }
}
void TrackBot::actionFire(Battlefield* battlefield, int dx, int dy){
    if(shells_<=0){
        cout << robotName_ << " (" << id_ << ") [TRACKBOT] is out of ammo! Self-destructs!" << endl;
        logFile << robotName_ << " (" << id_ << ") [TRACKBOT] is out of ammo! Self-destructs!" << endl;
        numOfLives_=0; battlefield->getBattlefieldGrid()[robotPositionY][robotPositionX]="*"; battlefield->addDestroyedRobot(this); return;
    }
    shells_--;
    if(dx==0 && dy==0){
        cout << robotName_ << " (" << id_ << ") [TRACKBOT] cannot fire at itself." << endl;
        logFile << robotName_ << " (" << id_ << ") [TRACKBOT] cannot fire at itself." << endl;
        return;
    }
    int tX=robotPositionX+dx; int tY=robotPositionY+dy;
    if(tY>=0 && tY<battlefield->BATTLEFIELD_NUM_OF_ROWS() && tX>=0 && tX<battlefield->BATTLEFIELD_NUM_OF_COLS()){
        string tc=battlefield->getBattlefieldGrid()[tY][tX];
        if(tc!="*"){
            Robot* tr=battlefield->getRobotAt(tX,tY);
            if(tr && tr->id()!=id_){
                if(tr->robotType()=="HideBot" && tr->isHidden()){
                    cout << "  " << id_ << " fired at " << tr->id() << " but it's hidden! Miss!" << endl;
                    logFile << "  " << id_ << " fired at " << tr->id() << " but it's hidden! Miss!" << endl;
                    return;
                }
                if(rand()%100 < 70){
                    cout << "  TRACKBOT HIT! " << id_ << " hit " << tr->id() << endl;
                    logFile << "  " << id_ << " hit " << tr->id() << endl;
                    tr->reduceLife();
                    if(!tr->isAlive()){battlefield->getBattlefieldGrid()[tY][tX]="*";battlefield->addDestroyedRobot(tr);incrementKills();}
                } else {
                    cout << "  TRACKBOT MISSED! " << id_ << " shot wide." << endl;
                    logFile << "  " << id_ << " shot wide." << endl;
                }
            }
        } else {
            cout << "  TRACKBOT shot hit empty space." << endl;
            logFile << "  TRACKBOT shot hit empty space." << endl;
        }
    } else {
        cout << "  TRACKBOT shot out of bounds." << endl;
        logFile << "  TRACKBOT shot out of bounds." << endl;
    }
}
void TrackBot::actionMove(Battlefield* battlefield){
    int mvs[9][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,0},{0,1},{1,-1},{1,0},{1,1}};
    int mi=rand()%9; int dx=mvs[mi][1]; int dy=mvs[mi][0];
    int nX=robotPositionX+dx; int nY=robotPositionY+dy;
    if(nY>=0 && nY<battlefield->BATTLEFIELD_NUM_OF_ROWS() && nX>=0 && nX<battlefield->BATTLEFIELD_NUM_OF_COLS()){
        if(battlefield->getBattlefieldGrid()[nY][nX]=="*"){
            battlefield->getBattlefieldGrid()[robotPositionY][robotPositionX]="*"; setX(nX);setY(nY); battlefield->getBattlefieldGrid()[nY][nX]=id_;
            cout << "  " << id_ << " [TRACKBOT] moved to (" << nX << ", " << nY << ")" << endl;
            logFile << "  " << id_ << " [TRACKBOT] moved to (" << nX << ", " << nY << ")" << endl;
        } else {
            cout << "  " << id_ << " [TRACKBOT] can't move - space occupied." << endl;
            logFile << "  " << id_ << " [TRACKBOT] can't move - space occupied." << endl;
        }
    } else {
        cout << "  " << id_ << " [TRACKBOT] can't move - out of bounds." << endl;
        logFile << "  " << id_ << " [TRACKBOT] can't move - out of bounds." << endl;
    }
}
void TrackBot::actions(Battlefield* battlefield){
    int offs[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
    actionThink(battlefield);
    int ldx=(rand()%3)-1; int ldy=(rand()%3)-1; actionLook(battlefield,ldx,ldy);
    int fi=rand()%8; int fdx=offs[fi][1]; int fdy=offs[fi][0]; actionFire(battlefield,fdx,fdy);
    actionMove(battlefield);
}

int Battlefield::BATTLEFIELD_NUM_OF_COLS() const { return BATTLEFIELD_NUM_OF_COLS_; }
int Battlefield::BATTLEFIELD_NUM_OF_ROWS() const { return BATTLEFIELD_NUM_OF_ROWS_; }
int Battlefield::turns() const { return turns_; }
int Battlefield::numOfRobots() const { return robots_.size(); }
vector<Robot*>& Battlefield::getRobots() { return robots_; }
vector<vector<string>>& Battlefield::getBattlefieldGrid() { return battlefield_grid_; }
queue<Robot*>& Battlefield::getReentryQueue() { return reentryQueue_; }

void Battlefield::addDestroyedRobot(Robot* r) {
    r->incrementReentryAttempts();
    if (r->getReentryAttempts() <= 3) {
        if (r->x() != -1 && r->y() != -1 && r->y() < BATTLEFIELD_NUM_OF_ROWS_ && r->x() < BATTLEFIELD_NUM_OF_COLS_) {
            battlefield_grid_[r->y()][r->x()] = "*";
        }
        reentryQueue_.push(r);
        cout << "  " << r->robotName() << " (" << r->id() << ") destroyed. Will attempt re-entry (attempt " << r->getReentryAttempts() << "/3)." << endl;
        logFile << "  " << r->robotName() << " (" << r->id() << ") destroyed. Will attempt re-entry (attempt " << r->getReentryAttempts() << "/3)." << endl;
    } else {
        cout << "  " << r->robotName() << " (" << r->id() << ") permanently destroyed (exceeded re-entry attempts)." << endl;
        logFile << "  " << r->robotName() << " (" << r->id() << ") permanently destroyed (exceeded re-entry attempts)." << endl;
        if (r->x() != -1 && r->y() != -1 && r->y() < BATTLEFIELD_NUM_OF_ROWS_ && r->x() < BATTLEFIELD_NUM_OF_COLS_) {
            battlefield_grid_[r->y()][r->x()] = "*";
        }
        destroyedRobots_.push(r);
    }
}

Robot* Battlefield::getRobotAt(int x, int y) {
    if (y >= 0 && y < BATTLEFIELD_NUM_OF_ROWS_ && x >= 0 && x < BATTLEFIELD_NUM_OF_COLS_) {
        string id_at_pos = battlefield_grid_[y][x];
        if (id_at_pos != "*") {
            for (Robot* r_ptr : robots_) { // Changed r to r_ptr to avoid conflict
                if (r_ptr->id() == id_at_pos) {
                    return r_ptr;
                }
            }
        }
    }
    return nullptr;
}

void Battlefield::readFile(string filename) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) { cerr << "Error opening file: " << filename << endl; logFile << "Error opening file: " << filename << endl; exit(1); }
    string line; int line_num = 0;
    while (getline(inputFile, line)) {
        line_num++;
        if (line.empty() || line.find_first_not_of(" \t\n\r\f\v") == string::npos) continue;
        stringstream ss(line); string key; ss >> key;
        if (key == "M") {
            string by, N_str, colon; int tc, tr;
            if (!(ss >> by >> N_str >> colon >> tc >> tr)) { cerr << "Error: Malformed 'M by N' line " << line_num << endl; logFile << "Error: Malformed 'M by N' line " << line_num << endl; exit(1); }
            BATTLEFIELD_NUM_OF_COLS_ = tc; BATTLEFIELD_NUM_OF_ROWS_ = tr;
            battlefield_grid_.resize(BATTLEFIELD_NUM_OF_ROWS_);
            for (int i=0; i<BATTLEFIELD_NUM_OF_ROWS_; ++i) battlefield_grid_[i].resize(BATTLEFIELD_NUM_OF_COLS_);
        } else if (key == "steps:") {
            if (!(ss >> turns_)) { cerr << "Error reading steps from line " << line_num << endl; logFile << "Error reading steps from line " << line_num << endl; exit(1); }
        } else if (key == "robots:") {
            if (!(ss >> numOfRobots_)) { cerr << "Error reading number of robots from line " << line_num << endl; logFile << "Error reading number of robots from line " << line_num << endl; exit(1); }
        } else if (key == "GenericRobot") {
            string rName, x_str, y_str;
            if (!(ss >> rName >> x_str >> y_str)) { cerr << "Error reading robot details line " << line_num << endl; logFile << "Error reading robot details line " << line_num << endl; exit(1); }
            int x,y;
            if (x_str=="random" && y_str=="random") {
                if (BATTLEFIELD_NUM_OF_COLS_ == -1 || BATTLEFIELD_NUM_OF_ROWS_ == -1) { cerr << "Error: Battlefield dimensions not set for random." << endl; logFile << "Error: Battlefield dimensions not set for random." << endl; exit(1); }
                x=rand()%BATTLEFIELD_NUM_OF_COLS_; y=rand()%BATTLEFIELD_NUM_OF_ROWS_;
            } else { try {x=stoi(x_str); y=stoi(y_str);} catch(const exception& e){cerr<<"Error: Invalid coordinate line "<<line_num<<endl; logFile<<"Error: Invalid coordinate line "<<line_num<<endl; exit(1);}}
            string genId = "GRO" + to_string(robots_.size()+1);
            Robot* newRobot = new GenericRobot(genId,x,y);
            newRobot->setRobotName(rName); newRobot->setRobotType("GenericRobot");
            robots_.push_back(newRobot);
        }
    }
    inputFile.close();
}

void Battlefield::placeRobots() {
    if (BATTLEFIELD_NUM_OF_COLS_ == -1 || BATTLEFIELD_NUM_OF_ROWS_ == -1) { cerr << "Error: Battlefield dimensions not initialized." << endl; logFile << "Error: Battlefield dimensions not initialized." << endl; exit(1); }
    for (int i=0; i<BATTLEFIELD_NUM_OF_ROWS_; ++i) for (int j=0; j<BATTLEFIELD_NUM_OF_COLS_; ++j) battlefield_grid_[i][j] = "*";
    for (Robot* robot : robots_) {
        if (robot->y() >= 0 && robot->y() < BATTLEFIELD_NUM_OF_ROWS_ && robot->x() >=0 && robot->x() < BATTLEFIELD_NUM_OF_COLS_) {
            battlefield_grid_[robot->y()][robot->x()] = robot->id();
        } else { cerr << "Error: Invalid initial location for robot " << robot->robotName() << endl; logFile << "Error: Invalid initial location for robot " << robot->robotName() << endl; exit(1); }
    }
}

void Battlefield::displayBattlefield() const {
    cout << "\nDisplay Battlefield" << endl;                        logFile << "\nDisplay Battlefield" << endl;
    cout << "    "; logFile << "    ";
    for (int j = 0; j < BATTLEFIELD_NUM_OF_COLS_; ++j) { cout << "  " << right << setfill('0') << setw(2) << j << " "; logFile << "  " << right << setfill('0') << setw(2) << j << " ";}
    cout << endl; logFile << endl;
    for (int i = 0; i < BATTLEFIELD_NUM_OF_ROWS_; ++i) {
        cout << "    "; logFile << "    ";
        for (int j = 0; j < BATTLEFIELD_NUM_OF_COLS_; ++j) { cout << "+----"; logFile << "+----"; }
        cout << "+" << endl; logFile << "+" << endl;
        cout << "  " << right << setfill('0') << setw(2) << i; logFile << "  " << right << setfill('0') << setw(2) << i;
        for (int j = 0; j < BATTLEFIELD_NUM_OF_COLS_; ++j) { cout << "|" << left << setfill(' ') << setw(4) << battlefield_grid_[i][j]; logFile << "|" << left << setfill(' ') << setw(4) << battlefield_grid_[i][j]; }
        cout << "|" << endl; logFile << "|" << endl;
    }
    cout << "    "; logFile << "    ";
    for (int j = 0; j < BATTLEFIELD_NUM_OF_COLS_; ++j) { cout << "+----"; logFile << "+----"; }
    cout << "+" << endl; logFile << "+" << endl;
}

// ====================================================================
// MAIN SIMULATION LOGIC
// ====================================================================
int main() {
    logFile.open("simulation_log.txt");
    if (!logFile.is_open()) {
        cerr << "Error: Could not open log file for writing." << endl;
        return 1;
    }

    srand(static_cast<unsigned int>(time(0)));
    Battlefield battlefield;
    battlefield.readFile("Input.txt");
    battlefield.placeRobots();
    battlefield.displayBattlefield();

    cout << "\nStarting Simulation..." << endl;
    logFile << "\nStarting Simulation..." << endl;

    int activeRobotsCount;
    for (int currentTurn = 1; currentTurn <= battlefield.turns(); ++currentTurn) {
        cout << "\n--- Turn " << currentTurn << " ---" << endl;
        logFile << "\n--- Turn " << currentTurn << " ---" << endl;

        if (!battlefield.getReentryQueue().empty()) {
            Robot* reenteringRobot = battlefield.getReentryQueue().front();
            battlefield.getReentryQueue().pop();
            int newX, newY; bool spotFound = false;
            int maxAttempts = battlefield.BATTLEFIELD_NUM_OF_ROWS() * battlefield.BATTLEFIELD_NUM_OF_COLS();
            int attempts = 0;
            do {
                newX = rand() % battlefield.BATTLEFIELD_NUM_OF_COLS();
                newY = rand() % battlefield.BATTLEFIELD_NUM_OF_ROWS();
                if (battlefield.getBattlefieldGrid()[newY][newX] == "*") spotFound = true;
                attempts++;
            } while (!spotFound && attempts < maxAttempts);

            if (spotFound) {
                string reenteredId = reenteringRobot->id();
                Robot* newGenericRobot = new GenericRobot(reenteredId, newX, newY);
                newGenericRobot->setRobotName(reenteringRobot->robotName());
                newGenericRobot->setReentryAttempts(reenteringRobot->getReentryAttempts());
                bool replaced = false;
                for (size_t k = 0; k < battlefield.getRobots().size(); ++k) {
                    if (battlefield.getRobots()[k] == reenteringRobot) {
                        delete reenteringRobot; // Delete the old robot object
                        battlefield.getRobots()[k] = newGenericRobot;
                        replaced = true; break;
                    }
                }
                if (!replaced) {
                    battlefield.getRobots().push_back(newGenericRobot);
                    cout << "  Warning: Re-entering robot not found in active list, adding as new." << endl;
                    logFile << "  Warning: Re-entering robot not found in active list, adding as new." << endl;
                }
                battlefield.getBattlefieldGrid()[newY][newX] = newGenericRobot->id();
                cout << "  " << newGenericRobot->robotName() << " (" << newGenericRobot->id() << ") re-entered battlefield at (" << newX << ", " << newY << ")!" << endl;
                logFile << "  " << newGenericRobot->robotName() << " (" << newGenericRobot->id() << ") re-entered battlefield at (" << newX << ", " << newY << ")!" << endl;
            } else {
                cout << "  " << reenteringRobot->robotName() << " (" << reenteringRobot->id() << ") could not re-enter: no empty spot found. Permanently destroyed." << endl;
                logFile << "  " << reenteringRobot->robotName() << " (" << reenteringRobot->id() << ") could not re-enter: no empty spot found. Permanently destroyed." << endl;
                battlefield.addDestroyedRobot(reenteringRobot); // This will now push to destroyedRobots_ queue as attempts > 3
            }
        }

        activeRobotsCount = 0;
        for (Robot* r_ptr : battlefield.getRobots()) { // Changed r to r_ptr
            if (r_ptr->isAlive()) activeRobotsCount++;
        }
        if (activeRobotsCount <= 1) {
            cout << "\nSimulation ended: " << activeRobotsCount << " robot(s) remaining." << endl;
            logFile << "\nSimulation ended: " << activeRobotsCount << " robot(s) remaining." << endl;
            break;
        }

        for (size_t i = 0; i < battlefield.getRobots().size(); ++i) {
            Robot* currentRobot = battlefield.getRobots()[i];
            if (currentRobot->isAlive()) {
                cout << currentRobot->robotName() << " (" << currentRobot->id() << ") performs actions:" << endl;
                logFile << currentRobot->robotName() << " (" << currentRobot->id() << ") performs actions:" << endl;
                currentRobot->actions(&battlefield);
            } else {
                cout << currentRobot->robotName() << " (" << currentRobot->id() << ") is destroyed, skipping turn." << endl;
                logFile << currentRobot->robotName() << " (" << currentRobot->id() << ") is destroyed, skipping turn." << endl;
            }
        }
        battlefield.displayBattlefield();
    }

    cout << "\n--- Final Status ---" << endl;
    logFile << "\n--- Final Status ---" << endl;

    // Collect all robots for ranking (both alive and dead)
    vector<Robot*> allRobots = battlefield.getRobots();

    // Sort robots based on the specified criteria
    sort(allRobots.begin(), allRobots.end(), [](const Robot* a, const Robot* b) {
        // 1. Alive vs. Dead
        if (a->isAlive() && !b->isAlive()) return true;
        if (!a->isAlive() && b->isAlive()) return false;

        // If both are alive or both are dead, compare by kills
        if (a->numOfKills() != b->numOfKills()) {
            return a->numOfKills() > b->numOfKills(); // More kills is better
        }

        // If kills are tied, compare by lives
        return a->numOfLives() > b->numOfLives(); // More lives is better
    });

    cout << "\n--- Robot Ranking ---" << endl;
    logFile << "\n--- Robot Ranking ---" << endl;
    for (size_t i = 0; i < allRobots.size(); ++i) {
        Robot* r = allRobots[i];
        cout << (i + 1) << ". " << r->robotName() << " (" << r->id() << ") - Status: "
             << (r->isAlive() ? "Alive" : "Destroyed")
             << ", Kills: " << r->numOfKills()
             << ", Lives: " << r->numOfLives()
             << ", Shells: " << r->getShells() << endl;
        logFile << (i + 1) << ". " << r->robotName() << " (" << r->id() << ") - Status: "
                << (r->isAlive() ? "Alive" : "Destroyed")
                << ", Kills: " << r->numOfKills()
                << ", Lives: " << r->numOfLives()
                << ", Shells: " << r->getShells() << endl;
    }

    activeRobotsCount = 0;
    for (Robot* r_ptr : battlefield.getRobots()) {
        if (r_ptr->isAlive()) {
            activeRobotsCount++;
        }
    }

    // Determine simulation outcome based on new rules
    if (activeRobotsCount == 0) {
        cout << "\nAll robots destroyed. No clear winner." << endl;
        logFile << "\nAll robots destroyed. No clear winner." << endl;
    } else if (activeRobotsCount == 1) {
        cout << "\nOne robot remains victorious: " << allRobots[0]->robotName()
             << " (" << allRobots[0]->id() << ")!" << endl;
        logFile << "\nOne robot remains victorious: " << allRobots[0]->robotName()
                 << " (" << allRobots[0]->id() << ")!" << endl;
    } else {
        // Multiple robots remain, determine winner by kills (already handled by sorting, now just declare)
        int maxKills = allRobots[0]->numOfKills(); // Top robot in sorted list has max kills
        vector<Robot*> topKillers;
        for (Robot* r : allRobots) {
            if (r->isAlive() && r->numOfKills() == maxKills) {
                topKillers.push_back(r);
            }
        }

        if (topKillers.size() == 1) {
            cout << "\nMultiple robots remain. Winner determined by kills: " << topKillers[0]->robotName()
                 << " (" << topKillers[0]->id() << ") with " << topKillers[0]->numOfKills() << " kills!" << endl;
            logFile << "\nMultiple robots remain. Winner determined by kills: " << topKillers[0]->robotName()
                    << " (" << topKillers[0]->id() << ") with " << topKillers[0]->numOfKills() << " kills!" << endl;
        } else {
            cout << "\nMultiple robots remain. It's a draw among top killers with " << maxKills << " kills: ";
            logFile << "\nMultiple robots remain. It's a draw among top killers with " << maxKills << " kills: ";
            for (size_t i = 0; i < topKillers.size(); ++i) {
                cout << topKillers[i]->robotName() << " (" << topKillers[i]->id() << ")";
                logFile << topKillers[i]->robotName() << " (" << topKillers[i]->id() << ")";
                if (i < topKillers.size() - 1) {
                    cout << ", ";
                    logFile << ", ";
                }
            }
            cout << "!" << endl;
            logFile << "!" << endl;
        }
    }

    // Clean up dynamically allocated robot objects to prevent memory leaks
    // First, clean up any robots still in the reentryQueue (if simulation ended early)
    while (!battlefield.getReentryQueue().empty()) {
        Robot* r_ptr = battlefield.getReentryQueue().front();
        battlefield.getReentryQueue().pop();
        delete r_ptr;
    }
    // Then, clean up all robots in the main robots_ vector
    for (Robot* r_ptr : battlefield.getRobots()) {
        delete r_ptr;
    }
    // Also clear the vector to prevent double deletion if pointers were moved
    battlefield.getRobots().clear();

    logFile.close(); // Close the log file
    return 0;
}
