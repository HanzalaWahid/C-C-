#include "SnakeWindow.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
    try{
    QApplication app(argc, argv);
    SnakeWindow window;
    //window.show();
    window.showFullScreen();
    return app.exec();
}
catch(...) {
    qDebug() << "Unknown Error\n";
}
#ifndef SNAKEWINDOW_H
#define SNAKEWINDOW_H

#include <QWidget>

namespace Ui {
class SnakeWindow;
}

class SnakeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SnakeWindow(QWidget *parent = nullptr);
    ~SnakeWindow();

private:
    Ui::SnakeWindow *ui;
};



#endif // SNAKEWINDOW_H
#include "SnakeWindow.h"
#include "ui_SnakeWindow.h"

SnakeWindow::SnakeWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SnakeWindow)
{
    ui->setupUi(this);

    connect(ui->startButton, &QPushButton::clicked,
            ui->snakeBoard, &SnakeBoard::start);
    connect(ui->quitButton, &QPushButton::clicked,
            qApp, &QApplication::quit);
    connect(ui->pauseButton, &QPushButton::clicked,
            ui->snakeBoard, &SnakeBoard::pause);
    connect(ui->snakeBoard, &SnakeBoard::scoreChanged,
            [=](int score) {ui->scoreLcd->display(score);});
    connect(ui->snakeBoard, &SnakeBoard::delayChanged,
            [=](int level) {ui->delayLcd->display(level);});
}

SnakeWindow::~SnakeWindow()
{
    delete ui;
}
#ifndef SNAKEBOARD_H
#define SNAKEBOARD_H

#include <QFrame>
#include <QBasicTimer>

#include "Board.h"

class SnakeBoard : public QFrame {
    Q_OBJECT
public:
    SnakeBoard(QWidget* parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

public slots:
    void start();
    void pause();
    void gameOver();

signals:
    void scoreChanged(int score);
    void delayChanged(int delay);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    int squareWidth();
    int squareHeight();

    void drawField(
        QPainter& painter, int x, int y, snakeGame::FieldType fieldType);

    void drawWall(QPainter& painter, int x, int y);
    void drawFood(QPainter& painter, int x, int y);

    void drawSnakeHead(QPainter& painter, int x, int y);
    void drawSnakeSegment(QPainter& painter, int x, int y);

    static constexpr auto boardWidth{40};
    static constexpr auto boardHeight{20};

    static constexpr auto initDelay{300};
    static constexpr auto initPoints{100};

    QBasicTimer timer;

    snakeGame::Board board{boardWidth, boardHeight};
    snakeGame::SnakeDirection snakeDirection{snakeGame::SnakeDirection::right};

    bool isStarted{false};
    bool isPaused{false};
    bool isGameOver{false};
    bool snakeWasMoved{true};
    int score{0};
    int delay{initDelay};
    int points{initPoints};
};

#endif // SNAKEBOARD_H
#include "SnakeBoard.h"

#include <QKeyEvent>
#include <QColor>
#include <QPainter>
#include <QRgb>
#include <QTimerEvent>

#include <QDebug>

using namespace snakeGame;

SnakeBoard::SnakeBoard(QWidget* parent)
    : QFrame{parent},
    board{boardWidth, boardHeight},
    snakeDirection{SnakeDirection::right}
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);

    board.updateSnakePosition();
    board.placeFood();
}

QSize SnakeBoard::sizeHint() const
{
    return QSize(boardWidth * 15 + frameWidth() * 2,
                 boardHeight * 15 + frameWidth() * 2);
}

QSize SnakeBoard::minimumSizeHint() const
{
    return QSize(boardWidth * 5 + frameWidth() * 2,
                 boardHeight * 5 + frameWidth() * 2);
}

void SnakeBoard::start()
{
    if (isGameOver) {
        isGameOver = false;
        board.reset();
        board.updateSnakePosition();
        board.placeFood();

        score = 0;
        points = initPoints;
        delay = initDelay;
    }

    if (isPaused)
        return;

    isStarted = true;

    emit scoreChanged(score);
    emit delayChanged(delay);

    timer.start(delay, this);
}

void SnakeBoard::pause()
{
    if (!isStarted)
        return;

    isPaused = !isPaused;
    if (isPaused) {
        timer.stop();
    }
    else {
        timer.start(delay, this);
    }
    update();
}

void SnakeBoard::gameOver()
{
    timer.stop();
    isGameOver = true;
    isStarted = false;
}

void SnakeBoard::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    QRect rect = contentsRect();


    if(isGameOver) {
        QFont font;
        font.setPixelSize(20);
        painter.setFont(font);
        painter.drawText(rect, Qt::AlignCenter, tr("Game Over"));
        return;
    }

    if(!isStarted) {
        QFont font;
        font.setPixelSize(20);
        painter.setFont(font);
        painter.drawText(rect, Qt::AlignCenter, tr(
            "Press start\n Use arrow keys to control the Snake"));
        return;
    }

    if (isPaused) {
        QFont font;
        font.setPixelSize(20);
        painter.setFont(font);
        painter.drawText(rect, Qt::AlignCenter, tr("Pause"));
        return;
    }

    auto boardTop = rect.bottom() - boardHeight * squareHeight();

    for (int i = 0; i < boardHeight; ++i) {
        for (int j = 0; j < boardWidth; ++j) {
            auto fieldType =
                board.fieldTypeAt(
                    static_cast<std::size_t>(j),
                    static_cast<std::size_t>(i));
            drawField(painter, rect.left() + j * squareWidth(),
                      boardTop + i * squareHeight(), fieldType);
        }
    }
}


void SnakeBoard::keyPressEvent(QKeyEvent *event)
{
    auto key = event->key();

    if (key == Qt::Key_P) {
        emit pause();
    }
    if (key == Qt::Key_Space) {
        emit start();
    }
    else if (!isStarted || isGameOver || !snakeWasMoved) {
        QFrame::keyPressEvent(event);
        return;
    }

    switch (key) {
    case Qt::Key_Left:       
        if (snakeDirection != SnakeDirection::right) {
            snakeDirection = SnakeDirection::left;
            snakeWasMoved = false;
        }
        break;
    case Qt::Key_Right:
        if (snakeDirection != SnakeDirection::left) {
            snakeDirection = SnakeDirection::right;
            snakeWasMoved = false;
        }
        break;
    case Qt::Key_Down:
        if (snakeDirection != SnakeDirection::up) {
            snakeDirection = SnakeDirection::down;
            snakeWasMoved = false;
        }
        break;
    case Qt::Key_Up:
        if (snakeDirection != SnakeDirection::down) {
            snakeDirection = SnakeDirection::up;
            snakeWasMoved = false;
        }
        break;
    default:
        QFrame::keyPressEvent(event);
    }
}

void SnakeBoard::timerEvent(QTimerEvent *event)
{
    if (isGameOver){
        QFrame::timerEvent(event);
        return;
    }

    if (event->timerId() == timer.timerId()) {

        board.moveSnake(snakeDirection);
        snakeWasMoved = true;

        if (board.snakeHitFood()) {
            board.eatFood();
            board.growSnake();
            board.updateSnakePosition();
            board.placeFood();
            score += points;
            points += static_cast<double>(initDelay / delay) * initPoints;
            delay -= 4;

            emit scoreChanged(score);
            emit delayChanged(delay);
        }
        else if (board.snakeHitWall() || board.snakeHitSnake()) {
            emit gameOver();
        }
        else {
            board.updateSnakePosition();
        }

        update();

        timer.start(delay, this);
    }
    else {
        QFrame::timerEvent(event);
    }
}

int SnakeBoard::squareWidth()
{
    return contentsRect().width() / boardWidth;
}

int SnakeBoard::squareHeight()
{
    return contentsRect().height() / boardHeight;
}

void SnakeBoard::drawField(
    QPainter& painter, int x, int y, snakeGame::FieldType fieldType)
{
    switch(fieldType){
    case FieldType::empty:
        break;
    case FieldType::wall:
        drawWall(painter, x, y);
        break;
    case FieldType::food:
        drawFood(painter, x, y);
        break;
    case FieldType::snakeHead:
        drawSnakeHead(painter, x, y);
        break;
    case FieldType::snakeSegment:
        drawSnakeSegment(painter, x, y);
        break;
    }
}

void SnakeBoard::drawWall(QPainter& painter, int x, int y)
{
    constexpr auto colorBrown = 0xbf8040;

    QColor color = QRgb{colorBrown};
    painter.fillRect(x + 1, y + 1, squareWidth() - 2, squareHeight() - 2,
                     color);

    painter.setPen(color.light());
    painter.drawLine(x, y + squareHeight() - 1, x, y);
    painter.drawLine(x, y, x + squareWidth() - 1, y);

    painter.setPen(color.dark());
    painter.drawLine(x + 1, y + squareHeight() - 1,
                     x + squareWidth() - 1, y + squareHeight() - 1);
    painter.drawLine(x + squareWidth() - 1, y + squareHeight() - 1,
                     x + squareWidth() - 1, y + 1);
}

void SnakeBoard::drawFood(QPainter& painter, int x, int y)
{
    constexpr auto colorRed = 0xff0000;
    QColor color = QRgb{colorRed};
    painter.setPen(color.light());
    painter.setBrush(QBrush{color});
    painter.drawEllipse(x +1,y +1,squareWidth() -3, squareHeight() -3);
}

void SnakeBoard::drawSnakeHead(QPainter& painter, int x, int y)
{
    constexpr auto colorDarkerLimeGreen = 0x00b300;

    QColor color = QRgb{colorDarkerLimeGreen};
    painter.fillRect(x + 1, y + 1, squareWidth() - 2, squareHeight() - 2,
                     color);

    painter.setPen(color.light());
    painter.drawLine(x, y + squareHeight() - 1, x, y);
    painter.drawLine(x, y, x + squareWidth() - 1, y);

    painter.setPen(color.dark());
    painter.drawLine(x + 1, y + squareHeight() - 1,
                     x + squareWidth() - 1, y + squareHeight() - 1);
    painter.drawLine(x + squareWidth() - 1, y + squareHeight() - 1,
                     x + squareWidth() - 1, y + 1);
}

void SnakeBoard::drawSnakeSegment(QPainter& painter, int x, int y)
{
    constexpr auto colorLimeGreen = 0x00e600;

    QColor color = QRgb{colorLimeGreen};
    painter.fillRect(x + 1, y + 1, squareWidth() - 2, squareHeight() - 2,
                     color);

    painter.setPen(color.light());
    painter.drawLine(x, y + squareHeight() - 1, x, y);
    painter.drawLine(x, y, x + squareWidth() - 1, y);

    painter.setPen(color.dark());
    painter.drawLine(x + 1, y + squareHeight() - 1,
                     x + squareWidth() - 1, y + squareHeight() - 1);
    painter.drawLine(x + squareWidth() - 1, y + squareHeight() - 1,
                     x + squareWidth() - 1, y + 1);
}
#ifndef BOARD_H
#define BOARD_H

#include "Snake.h"

#include <vector>
#include <random>
#include <iosfwd>

namespace snakeGame {

    enum class SnakeDirection;

    enum class FieldType {
        empty,
        snakeSegment,
        snakeHead,
        wall,
        food
    };

    enum class SnakeDirection {
        up, right, down, left
    };

    class Board
    {
    public:
        Board(std::size_t width, std::size_t height);

        void reset();

        void placeFood();
        void updateSnakePosition();
        bool snakeHitFood() const;
        void eatFood();
        void growSnake();
        bool snakeHitWall() const;
        bool snakeHitSnake() const;
        void moveSnake(SnakeDirection snakeDirection);

        void debugPrintSnakeCoordinates();

        FieldType fieldTypeAt(std::size_t x, std::size_t y);
    private:
        std::vector<std::vector<FieldType>> initFieldWithWalls(
            std::size_t width, std::size_t height);
        void removeOldSnakePosition(const std::vector<SnakeSegment>& body);
        void addNewSnakePosition(const std::vector<SnakeSegment>& body);

        const std::size_t mWidth;
        const std::size_t mHeight;

        Snake mSnake;
        std::vector<std::vector<FieldType>> mFields;

        std::random_device mRandomDevice;
        std::default_random_engine mGenerator;
        std::uniform_int_distribution<std::size_t> mWidthDistribution;
        std::uniform_int_distribution<std::size_t> mHeightDistribution;

        friend std::wostream& operator<<(std::wostream& os, const Board& obj);
    };

    std::wostream& operator<<(std::wostream& os, const Board& obj);

}
#endif
#include "Board.h"

#include <algorithm>
#include <iostream>

namespace snakeGame {

    Board::Board(std::size_t width, std::size_t height)
        : mWidth{width},
        mHeight{height},
        mSnake{ width, height },
        mFields{ initFieldWithWalls(width, height) },
        mRandomDevice{},
        mGenerator{ mRandomDevice() },
        mWidthDistribution{ 2, width - 3 },
        mHeightDistribution{ 2, height - 3 }
    {
    }

    void Board::reset()
    {
        mFields = initFieldWithWalls(mWidth, mHeight);
        mSnake = Snake{mWidth,mHeight};
    }

    void Board::placeFood()
    {
        for (;;) {
            auto x = mWidthDistribution(mGenerator);
            auto y = mHeightDistribution(mGenerator);

            if(mFields.at(y).at(x) == FieldType::empty){
                mFields.at(y).at(x) = FieldType::food;
                return;
            }
        }
    }

    void Board::updateSnakePosition()
    {
        auto snakeBody = mSnake.getBody();

        removeOldSnakePosition(snakeBody);
        addNewSnakePosition(snakeBody);
    }

    bool Board::snakeHitFood() const
    {
        auto pos = mSnake.getBody().at(0).pos;
        return mFields.at(pos.y).at(pos.x) == FieldType::food;
    }

    void Board::eatFood()
    {
        auto pos = mSnake.getBody()[0].pos;
        mFields.at(pos.y).at(pos.x) = FieldType::empty;
    }

    void Board::growSnake()
    {
        mSnake.grow();
    }

    bool Board::snakeHitWall() const
    {
        auto pos = mSnake.getBody()[0].pos;
        return mFields.at(pos.y).at(pos.x) == FieldType::wall;
    }

    bool Board::snakeHitSnake() const
    {
        auto pos = mSnake.getBody()[0].pos;
        return mFields.at(pos.y).at(pos.x) == FieldType::snakeSegment;
    }

    void Board::moveSnake(SnakeDirection snakeDirection)
    {
        switch (snakeDirection) {
        case SnakeDirection::right:
            mSnake.moveRight();
            break;

        case SnakeDirection::down:
            mSnake.moveDown();
            break;

        case SnakeDirection::left:
            mSnake.moveLeft();
            break;

        case SnakeDirection::up:
            mSnake.moveUp();
            break;
        }
    }

    void Board::debugPrintSnakeCoordinates()
    {
        auto body = mSnake.getBody();

        for (std::size_t i = 0; i < body.size(); ++i) {
            auto pos = body.at(i).pos;

            std::wcout << "nr:" << i << "x:" << pos.x
                       << "\t" << "y:" << pos.y << "\t";

            auto field = mFields.at(pos.y).at(pos.x);

            switch(field)
            {
            case FieldType::snakeHead:
                std::wcout << L"Head\t";
                [[fallthrough]];
            case FieldType::snakeSegment:
                std::wcout << L"Body\n";
                [[fallthrough]];
            default:
                std::wcout << L"    \n";
            }
        }
    }

    FieldType Board::fieldTypeAt(std::size_t x, std::size_t y)
    {
        return mFields.at(y).at(x);
    }

    std::vector<std::vector<FieldType>> Board::initFieldWithWalls(
        std::size_t width, std::size_t height)
    {
        std::vector<FieldType> row(width, FieldType::empty);
        std::vector<std::vector<FieldType>> field(height, row);

        std::fill(field.at(0).begin(), field.at(0).end(), FieldType::wall);
        std::fill(field.at(field.size() - 1).begin(),
                  field.at(field.size() - 1).end(), FieldType::wall);

        for (auto it_row = field.begin() + 1;
             it_row < field.end() - 1; ++it_row) {
            (*it_row).at(0) = FieldType::wall;
            (*it_row).at(it_row->size() - 1) = FieldType::wall;
        }
        return field;
    }

    void Board::removeOldSnakePosition(const std::vector<SnakeSegment>& body)
    {
        for (const auto& snakeSegment : body) {
            auto prev = snakeSegment.prev;
            mFields.at(prev.y).at(prev.x) = FieldType::empty;
        }
    }

    void Board::addNewSnakePosition(const std::vector<SnakeSegment>& body)
    {
        auto first{ true };
        for (const auto& snakeSegment : body) {
            auto pos = snakeSegment.pos;

            if (first) {
                mFields.at(pos.y).at(pos.x) = FieldType::snakeHead;
                first = false;
            }
            else {
                mFields.at(pos.y).at(pos.x) = FieldType::snakeSegment;
            }
        }
    }


    std::wostream& operator<<(std::wostream& os, const Board& obj)
    {
        for (const auto& row : obj.mFields) {
            for (const auto& element : row) {

                switch(element){
                case FieldType::empty:
                    os << L' ';
                    break;
                case FieldType::wall:
                    os << L'#';
                    break;
                case FieldType::food:
                    os << L'*';
                    break;
                case FieldType::snakeHead:
                    os << L'@';
                    break;
                case FieldType::snakeSegment:
                    os << L'o';
                    break;
                }
            }
            os << '\n';
        }
        return os;
    }

}
#include "Snake.h"

namespace snakeGame {

    Snake::Snake(std::size_t fieldWidth, std::size_t fieldHeight)
        :mBody{ initSnake(fieldWidth, fieldHeight) }
    {
    }

    std::vector<SnakeSegment> Snake::getBody() const
    {
        return mBody;
    }


    void Snake::moveRight()
    {
        safeCurrentPosToLastOfFirstElement();
        ++mBody.at(0).pos.x;
        moveRemainingElements();
    }

    void Snake::moveDown()
    {
        safeCurrentPosToLastOfFirstElement();
        ++mBody.at(0).pos.y;
        moveRemainingElements();
    }

    void Snake::moveLeft()
    {
        safeCurrentPosToLastOfFirstElement();
        --mBody.at(0).pos.x;
        moveRemainingElements();
    }

    void Snake::moveUp()
    {
        safeCurrentPosToLastOfFirstElement();
        --mBody.at(0).pos.y;
        moveRemainingElements();
    }

    void Snake::grow()
    {
        mBody.push_back(SnakeSegment{
            {mBody.at(mBody.size() - 1).prev.x,
            mBody.at(mBody.size() - 1).prev.y}
        });
    }

    void Snake::safeCurrentPosToLastOfFirstElement()
    {
        mBody.at(0).prev.x = mBody.at(0).pos.x;
        mBody.at(0).prev.y = mBody.at(0).pos.y;
    }

    void Snake::moveRemainingElements()
    {
        for (std::size_t i = 1; i < mBody.size(); ++i) {
            mBody.at(i).prev.x = mBody.at(i).pos.x;
            mBody.at(i).prev.y = mBody.at(i).pos.y;
            mBody.at(i).pos.x = mBody.at(i - 1).prev.x;
            mBody.at(i).pos.y = mBody.at(i - 1).prev.y;
        }
    }


    std::vector<SnakeSegment> initSnake(
        std::size_t boardWidth, std::size_t boardHeight)
    {
        auto x = boardWidth / 2;
        auto y = boardHeight / 2;
        std::vector<SnakeSegment> body{
            SnakeSegment{ {x, y} },
            SnakeSegment{ {x - 1, y} },
        };
        return body;
    }

}
QT += widgets
CONFIG += c++17

SOURCES += \
    Board.cpp \
    Snake.cpp \
    SnakeBoard.cpp \
    SnakeWindow.cpp \
    main.cpp

HEADERS += \
    Board.h \
    Snake.h \
    SnakeBoard.h \
    SnakeWindow.h

FORMS += \
    SnakeWindow.ui