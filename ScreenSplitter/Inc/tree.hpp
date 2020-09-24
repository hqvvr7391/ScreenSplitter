#pragma once

#include <QObject>
#include <iostream>

#define ROOT 0
#define LEFT 1
#define RIGHT 2

#define FULL 0
#define VERT 1
#define HORZ 2

//#define TEST
using namespace std;



#ifndef TEST
typedef struct {
    int type;
    int ratio;   
} SplitData;

typedef struct {
    int* x;
    int* y;
}Point;




class SplitTree;

class SplitTreeNode {
    friend class SplitTree;
private:
    
public:
    SplitTreeNode(SplitData* datum, Point* t, Point* b) {
        this->data = *datum;
        this->topleft = t;
        this->bottomright = b;
        
        SplitData data{ 0,0 };

        switch (this->data.type) {
        case FULL:
            topright = nullptr;
            bottomleft = nullptr;
            break;

        case VERT:
            topright = new Point{ &this->data.ratio , bottomright->y };
            bottomleft = new Point{ &this->data.ratio, topleft->y };
            this->pleft = new SplitTreeNode(&data, topleft, topright);
            this->pright = new SplitTreeNode(&data, bottomleft, bottomright);
            break;
            
        case HORZ:
            topright = new Point{ bottomright->x, &this->data.ratio };
            bottomleft = new Point{ topleft->x, &this->data.ratio };
            this->pleft = new SplitTreeNode(&data, topleft, topright);
            this->pright = new SplitTreeNode(&data, bottomleft, bottomright);
            break;

        default:
            break;
        }

        
    }

    void updateNode(SplitData* datum, Point* t, Point* b) {
        this->data = *datum;
        this->topleft = t;
        this->bottomright = b;

        delete topright;
        delete bottomleft;

        SplitData data{ 0,0 };

        switch (this->data.type) {
        case FULL:
            topright = nullptr;
            bottomleft = nullptr;
            break;

        case VERT:
            topright = new Point{ &this->data.ratio , bottomright->y };
            bottomleft = new Point{ &this->data.ratio, topleft->y };
            this->pleft = new SplitTreeNode(&data, topleft, topright);
            this->pright = new SplitTreeNode(&data, bottomleft, bottomright);
            break;

        case HORZ:
            topright = new Point{ bottomright->x, &this->data.ratio };
            bottomleft = new Point{ topleft->x, &this->data.ratio };
            this->pleft = new SplitTreeNode(&data, topleft, topright);
            this->pright = new SplitTreeNode(&data, bottomleft, bottomright);
            break;

        default:
            break;
        }
    }

    ~SplitTreeNode()
    {
        delete topright;
        delete bottomleft;
    }


    SplitData data;

    Point* topleft = nullptr;
    Point* topright = nullptr;

    Point* bottomright = nullptr;
    Point* bottomleft = nullptr;

    SplitTreeNode* pleft = nullptr;
    SplitTreeNode* pright = nullptr;
};

class SplitTree {
private:
    SplitTreeNode* root = nullptr;
    SplitTreeNode* current = nullptr;
    char* preset_type = nullptr;
    char* name = nullptr;

    int* origin = new int;
    int* width = new int;
    int* height = new int;

    Point* porigin;
    Point* pend;

    
public:
    SplitTree() {
        root = nullptr;
        current = root;

        *origin = 0;
        *width = 100;
        *height = 100;

        porigin = new Point{ origin,origin };
        pend = new Point{ width, height };

        SplitData data { 0,0 };
        root = new SplitTreeNode(&data, porigin, pend);
    }
    
    
    SplitTreeNode* getRoot() {
        return root;
    }

    void setName(const char* ch, int length) {
        delete[] name;
        name = new char[length];
        strcpy(name, ch);
    }
    char* getName() {
        return name;
    }

    void setPresetTypeName(const char* ch, int length) {
        delete[] preset_type;
        preset_type = new char[length];
        strcpy(preset_type, ch);
    }
    char* getPresetTypeName() {
        return preset_type;
    }

    void setNode(SplitTreeNode* node, SplitData* data, int level) {

        switch (level) {
        case ROOT: {
            
            node->updateNode(data, porigin, pend);
            if (data->ratio == 0) {
                delete root;
                root = nullptr;
            }
            break;
         }
        case LEFT:
            node->updateNode(data, node->topleft, node->bottomright);
            break;
        case RIGHT:
            node->updateNode(data, node->topleft, node->bottomright);
            break;
        default:
            break;
        }
    }
};

#else

class SplitTree;

class SplitTreeNode {
    friend class SplitTree;
private:

public:
    SplitTreeNode(QRect* data, SplitTreeNode* left = nullptr, SplitTreeNode* right = nullptr) {
        this->data = data;
        this->left = left;
        this->right = right;
    }
    QRect* data;
    SplitTreeNode* left;
    SplitTreeNode* right;
};

class SplitTree {
private:

public:
    SplitTree() {
        root = new SplitTreeNode(QRect(0,0,100,100));
        current = root;
        
    }
    SplitTreeNode* root;
    SplitTreeNode* current;


    SplitTreeNode* getRoot() {
        return root;
    }

    void setNode(bool side, int ratio) {
        if (current != nullptr) {
            QRect* parentrect = current->data;
            if (!side) {
                current->left = new SplitTreeNode(parentrect);
                current->left->data->setY();
                current->left->data.setHeight()
                current = current->left;
            }
            else {
                current->right = new SplitTreeNode(data);
                current = current->right;
            }
        }
        else {
            root = new SplitTreeNode(data);
            current = root;
        }
    }

    void updateTree(SplitTreeNode* node)
    {
        if (node != nullptr) {
            updateRect(node);
            updateTree(node->left);
            updateTree(node->right);
        }
    }
    
    void updateRect(SplitTreeNode* node)
    {
        if (node != nullptr) {
            
        }
    }

    void visit(SplitTreeNode* current) {
        //cout << current->data << " ";
    }

    // 전위 순회 Current - Left - Right
    void preorder(SplitTreeNode* current) {
        if (current != nullptr) {
            visit(current);
            preorder(current->left);
            preorder(current->right);
        }
    }

    // 중위 순회 Left - Current - Right
    void inorder(SplitTreeNode* current) {
        if (current != nullptr) {
            inorder(current->left);
            visit(current);
            inorder(current->right);
        }
    }

    // 후위 순회 Left - Right - Current
    void postorder(SplitTreeNode* current) {
        if (current != nullptr) {
            postorder(current->left);
            postorder(current->right);
            visit(current);
        }
    }


};

#endif