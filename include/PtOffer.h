#ifndef PTOFFER_H
#define PTOFFER_H
#include "TreeNode.h"
class PtOffer
{
//Tree
    //二叉树深度
    int TreeDepth(TreeNode* pRoot)
    {
        return pRoot == NULL ? 0 : 1 + max(TreeDepth(pRoot->left), TreeDepth(pRoot->right));
    }

    //二叉树的镜像
    void Mirror(TreeNode *pRoot) {
        if(pRoot && (pRoot->left || pRoot->right)){
            swap(pRoot->left, pRoot->right);
            if(pRoot->left) Mirror(pRoot->left);
            if(pRoot->right) Mirror(pRoot->right);
        }
    }

    //平衡二叉树
    int balancedHeight(TreeNode* pRoot){
        //若是平衡二叉树，返回其高度，否则返回-1
        if(pRoot == NULL) return 0;
        else{
            if(pRoot->left == NULL && pRoot->right == NULL){
                return 1;
            }
            else if(pRoot->left != NULL && pRoot->right == NULL){
                return balancedHeight(pRoot->left) == 1 ? 2 : -1;
            }
            else if(pRoot->left == NULL && pRoot->right != NULL){
                return balancedHeight(pRoot->right) == 1 ? 2 : -1;
            }
            else{
                int a = balancedHeight(pRoot->right);
                int b = balancedHeight(pRoot->left);
                if(a != -1 && b != -1 && abs(a - b) <= 1) return max(a, b) + 1;
                else return -1;
            }
        }
    }
    bool IsBalanced_Solution(TreeNode* pRoot) {
		return balancedHeight(pRoot) == -1 ? false : true;
    }

    //把二叉树打印成多行
    void recursion(TreeNode* pRoot, vector<vector<int>> &vec, int index){
        if(pRoot == NULL) return;
        else vec[index].push_back(pRoot->val);
        recursion(pRoot->left, vec, index + 1);
        recursion(pRoot->right, vec, index + 1);
    }
    vector<vector<int> > Print(TreeNode* pRoot) {
        int h = TreeDepth(pRoot);
        if(pRoot == NULL) return {};
        vector<int> v{};
        vector<vector<int>> vec(h, v);
        int index = 0;
        recursion(pRoot, vec, index);
        return vec;
    }

    //对称的二叉树
    void Traversal(TreeNode* pRoot, vector<int> &vec, int order){
        if(pRoot == NULL) return;
        vec.push_back(pRoot->val);
        if(order){
        	Traversal(pRoot->left, vec, order);
        	Traversal(pRoot->right, vec, order);
        }
        else{
            Traversal(pRoot->right, vec, order);
        	Traversal(pRoot->left, vec, order);
        }
    }
    bool isSymmetrical(TreeNode* pRoot){
		vector<int> vec0, vec1;
        Traversal(pRoot, vec0, 0);
        Traversal(pRoot, vec1, 1);
        return vec0 == vec1;
    }
};

#endif // PTOFFER_H
