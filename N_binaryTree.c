

uint8	nodeIndex;

/**
 * Insert one node in rightmost of tree.
 * @param   parent [input]: Parent Node
 * @param   child  [input]: Child Node
 * @return  None.
 */
void insertAtEnd(nodeST* parent, nodeST* child)
{
    uint8 index = 1;

    if (parent->leftChild == NULL)
    	parent->leftChild = child;
    else
    {
        parent = (parent->leftChild);
        index++;
        while (parent->sibling != NULL)
        {
        	index++;
            parent = parent->sibling;
        }
        parent->sibling = child;
    }
    
    child->data.index = index;
    child->parent = parent;
}

/**
 * Insert one node.
 * @param   parent [input]: Parent Node
 * @param   child  [input]: Child Node
 * @return  None.
 */
void insertNode(nodeST* parent, nodeST* child)
{
    nodeST* previousNode = child->parent;

    if (previousNode->data.visible == FALSE)
    {
        if (parent->leftChild == NULL)	
            parent->leftChild = child;

        //this is first child
        if (child->data.index == 0)
        {
            child->sibling = parent->leftChild;
            parent->leftChild = child;
        }

        //this is not first parent's child
        else
        {
            parent = previousNode;
            while (parent && parent->data.visible == FALSE)
            {
                parent = parent->parent;
            }

            child->data.index = parent->data.index;
            child->sibling = parent->sibling;
            parent->sibling = child;
        }
    }
    else
    {
        if (parent->leftChild == NULL)	
        {
            parent->leftChild = child;
            child->data.index = 0;
        }
        else
        {
            child->sibling = previousNode->sibling;
            previousNode->sibling = child;
            child->data.index = previousNode->data.index;
        }
    }	
}

/**
 * Add child to last rightmost of the leaf.
 * @param    rootNode [input]: Root Node
 * @param    child [input]: child Node
 * @see      insertAtEnd().
 * @return   None.
 */
void addNode(nodeST* rootNode, nodeST* child)
{
    //add node to end of tree (preorder)
    nodeST* parent = getLastChild(rootNode);

    insertAtEnd(parent, child);
}

/**
 * Delete left child branch.
 * @param   parent [input]: Parent Node.
 * @param   menuNode [input]: Menu Node.
 * @return  None.
 */
void deleteNode(nodeST* parent, nodeST* menuNode)
{
    //delete left child branch
    //replace with sibling
    if (parent->leftChild == menuNode)
        parent->leftChild = menuNode->sibling;
    else if (parent->sibling == menuNode)
        parent->sibling = menuNode->sibling;
    
    menuNode->sibling = NULL;
}

/**
 * Delete last rightmost leaf.
 * @param   rootNode [input]: Root Node.
 * @see     deleteNode().     
 * @see     getLastParent().
 * @see     getLastChild().
 * @return  None. 
 */
void removeNode(nodeST* rootNode)
{
    //delete last rightmost leaf
    deleteNode(getLastParent(rootNode), getLastChild(rootNode));
}

/**
 * Preorder Traversal.
 * @param   root [input]: Root Node   
 * @return  None.   
 */
void preorderTraversal(nodeST* root)
{
    uint8   name[20] = {0};

    if (root != NULL) 
    {
    	strcpy(name, root->data.title);
    	preorderTraversal(root->leftChild);    // Print items in left subtree.
    	preorderTraversal(root->sibling);   // Print items in right subtree.
    }
}

/**
 * Postorder traversal.
 * @param   root [input]: Root Node  
 * @see     preorderTraversal(). 
 * @return  None.
 */
void postorderTraversal(nodeST* root)
{
    if (root != NULL) 
    {       
       preorderTraversal(root->leftChild);    // Print items in left subtree.
       preorderTraversal(root->sibling);   // Print items in right subtree.
    }
}

/**
 * Inorder Traversal.
 * @param   root [input]: Root Node 
 * @see     preorderTraversal().   
 * @return  None.
 */
void inorderTraversal(nodeST* root)
{
    if (root != NULL) 
    {       
       preorderTraversal(root->leftChild);    // Print items in left subtree.
       preorderTraversal(root->sibling);   // Print items in right subtree.
    }
}

/**
 * Search one node in tree.
 * @param   root [input]: Root Node 
 * @param   node [input]: Target Node
 * @see     searchNode().
 * @return  One node.
 */
nodeST* searchNode(nodeST* root, nodeST* node)
{
	if (root == NULL || strcmp(root->data.title, node->data.title) == 0)
		return root;
	else if (searchNode(root->leftChild, node) != NULL)
		return root->leftChild;
	else  
		return searchNode(root->sibling, node);
}

/**
 * Preorder Successor.
 * @param   menuNode [input]: Menu node is structure
 * @param   key [input]: is structure
 * @param   keyFound [input]: key for tree
 * @see     preorderSuccessor().
 * @return  One Node or NULL or Success.
 */
nodeST* preorderSuccessor(nodeST* menuNode, nodeST* key, uint8* keyFound)  
{ 
    nodeST* succs = NULL;

    if (menuNode != NULL) 
    { 
        if (key == menuNode) 
        { 
            *keyFound = TRUE; 
            if (menuNode->leftChild)
            {
                return menuNode->leftChild;
            }
            else
            {
                return menuNode->sibling;
            }
        } 
        succs = preorderSuccessor(menuNode->leftChild, key, keyFound); 
        if (succs == NULL) 
        { 
            if (*keyFound == TRUE)   /*case in which menuNode is the leftmost leaf of the left subtree*/
            {
                return menuNode->sibling;
            }
            else 
                return preorderSuccessor(menuNode->sibling, key, keyFound); 
        } 
        else 
            return succs; 
    } 
    return NULL; 
}  

/**
 * Get Successor.
 * @param   rootNode [input]: Root Node
 * @param   menuNode [input]: Menu Node
 * @see     preorderSuccessor().
 * @return  result.
 */
nodeST* successor(nodeST* rootNode, nodeST* menuNode)
{
    uint8   found   = FALSE;
    nodeST* result  = preorderSuccessor(rootNode, menuNode, &found);

    return result;
}

/**
 * Preorde Predecessor Traversal.
 * @param   parent [input]: Parent Node
 * @param   child [input]: Child Node
 * @see preorderPredecessor
 * @return  parent or NULL.
 */
nodeST* preorderPredecessor(nodeST* parent, nodeST* child)
{
    if (parent == NULL)
        return parent;
    
    if (parent->leftChild == child)
        return parent;
    else if (parent->sibling == child)
    {
        return parent;
    }
    else if (parent->leftChild == NULL && parent->sibling == NULL)
        return NULL;
    else if (parent->leftChild)
    {
        if (preorderPredecessor(parent->leftChild, child) == NULL)
            if (parent->sibling)
                preorderPredecessor(parent->sibling, child);
    }
    else if (parent->sibling)
    {
        preorderPredecessor(parent->sibling, child);
    }
}

/**
 * Get Predecessor.
 * @param   rootNode [input]: Root Node
 * @param   menuNode [input]: Menu Node
 * @see     preorderPredecessor().
 * @return  preorderPredecessor().
 */
nodeST* predecessor(nodeST* rootNode, nodeST* menuNode)
{
    return preorderPredecessor(rootNode, menuNode);
}

/**
 * Index will be 1.
 */
void resetIndex(void)
{
    nodeIndex = 1;
}

/**
 * Get parent Node.
 * @param   rootNode [input]: Root Node
 * @param   currentNode [input]: Current Node
 * @see     predecessor().
 * @return  currentNode.
 */
nodeST* getParentNode(nodeST* rootNode, nodeST* currentNode)
{
    nodeST* parent = predecessor(rootNode, currentNode);

    //go backward untill reach top level
    while (parent->sibling == currentNode)
    {
        currentNode = parent;
        parent = predecessor(rootNode, currentNode);
    }
    currentNode = parent;
    return currentNode;
}

/**
 * Get Previous Node.
 * @param   rootNode [input]: Root Node
 * @param   selectedNode [input]: Selected Node
 * @see     predecessor().
 * @return  predecessor().
 */
nodeST* getPreviousNode(nodeST* rootNode, nodeST* selectedNode)
{
    return predecessor(rootNode, selectedNode);
}

/**
 * Get Successor Node.
 * @param   rootNode [input]: Root Node
 * @param   selectedNode [input]: Selected Node
 * @see     successor().
 * @return  successor().
 */
nodeST* getSuccessorNode(nodeST* rootNode, nodeST* selectedNode)
{
    return successor(rootNode, selectedNode);	
}

/**
 * Get Next Node.
 * @param   currentNode [input]: Current Node
 * @return  Sibling Node.
 */
nodeST* getNextNode(nodeST* currentNode)
{	
    return currentNode->sibling;
}

/**
 * Get Child Node.
 * @param   currentNode [input]: Current Node
 * @return  Left child node.
 */
nodeST* getChildNode(nodeST* currentNode)
{
    return currentNode->leftChild;
}

/**
 * Get first sibling Node.
 * @param   rootNode [input]: Root Node
 * @param   currentNode [input]: Current Node
 * @see     predecessor().
 * @return  currentNode.
 */
nodeST* firstSibling(nodeST* rootNode, nodeST* currentNode)
{
    nodeST* parent = predecessor(rootNode, currentNode);

    while (parent->sibling == currentNode)
    {
        currentNode = parent;
        parent = predecessor(rootNode, currentNode);
    }	

    return currentNode;
}

/**
 * Get last sibling Node. 
 * @param   currentNode [input]: Current Node
 * @return  currentNode.
 */
nodeST* lastSibling(nodeST* currentNode)
{
    while (currentNode->sibling != NULL)
        currentNode = currentNode->sibling;

    return currentNode;
}

/**
 * Get First Node.
 * @param   rootNode [input]: Root Node
 * @param   currentNode [input]: Current Node
 * @see     firstSibling().
 * @return  firstSibling().
 */
nodeST* getFirstNode(nodeST* rootNode, nodeST* currentNode)
{
    return firstSibling(rootNode, currentNode);
}

/**
 * Get Last Node.
 * @param   currentNode [input]: Current Node
 * @see     lastSibling().
 * @return  lastSibling().
 */
nodeST* getLastNode(nodeST* currentNode)
{
    return lastSibling(currentNode);
}

/**
 * Get Last Child.
 * @param   rootNode [input]: Root Node
 * @see     successor().
 * @return  parentNode.
 */
nodeST* getLastChild(nodeST* rootNode)
{	
    nodeST* parentNode	= rootNode->leftChild;
    nodeST* currentNode = successor(rootNode, parentNode);

    while (currentNode != NULL)
    {
        parentNode = currentNode;
        currentNode = successor(rootNode, parentNode);
    }

    return parentNode;
}

/**
 * Get Last Parent.
 * @param   rootNode [input]: Root Node
 * @see     predecessor().
 * @see     getLastChild().
 * @return  parentNode. 
 */
nodeST* getLastParent(nodeST* rootNode)
{
    nodeST* parentNode = predecessor(rootNode, getLastChild(rootNode));

    return parentNode;
}

/**
 * Decrease Index.
 * @param   currentNode [input]: Current Node
 * @return  None.
 */
void decreaseIndex(nodeST* currentNode)
{
    //current node will be invisible
    //decrease next nodes index
    while (currentNode)
    {
        currentNode->data.index--;
        currentNode = currentNode->sibling;
    }
}

/**
 * 
 * @param   currentNode [input]: Current Node
 * @return  None.
 */
void increaseIndex(nodeST* currentNode)
{
    //currentNode will be visilble
    //increase next nodes index
    while (currentNode)
    {   
        currentNode->data.index++;
        currentNode = currentNode->sibling;
    }
}
