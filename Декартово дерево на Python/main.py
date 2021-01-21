import random


class Node:
    left = False
    right = False
    x = 0
    y = 0
    size = 0

    def __init__(self, val):
        self.x = val
        self.y = random.randint(0, 2 * 10 ** 9)
        self.size = 1

    def __del__(self):
        if self.left != False:
            del self.left
        if self.right != False:
            del self.right


def get_size(root):
    if root == False:
        return 0
    return root.size


def update(root):
    if root == False:
        return
    root.size = get_size(root.left) + get_size(root.right) + 1


def find(root, key):
    if root == False:
        return False
    if root.x == key:
        return True
    elif root.x > key:
        return find(root.left, key)
    else:
        return find(root.right, key)


def split(root, key):
    if root == False:
        return (False, False)
    if root.x <= key:
        root1, root2 = split(root.right, key)
        root.right = root1
        update(root)
        return (root, root2)
    else:
        root1, root2 = split(root.left, key)
        root.left = root2
        update(root)
        return (root1, root)


def merge(root1, root2):
    if root1 == False:
        return root2
    elif root2 == False:
        return root1
    if root1.y > root2.y:
        root1.right = merge(root1.right, root2)
        update(root1)
        return root1
    else:
        root2.left = merge(root1, root2.left)
        update(root2)
        return root2


def insert(root, key):
    if find(root, key):
        return root
    root1, root3 = split(root, key)
    root2 = Node(key)
    return merge(root1, merge(root2, root3))


def delete(root, key):
    if not find(root, key):
        return root
    root12, root3 = split(root, key)
    root1, root2 = split(root12, key - 1)
    return merge(root1, root3)


def next(root, key):
    if root == False:
        return 10 ** 10
    a = 10 ** 10
    b = 10 ** 10
    c = 10 ** 10
    if root.x > key:
        c = root.x
        b = next(root.left, key)
    if b == 10 ** 10 and c == 10 ** 10:
        a = next(root.right, key)
    return min(a, b, c)


def prev(root, key):
    if root == False:
        return -(10 ** 10)
    a = -(10 ** 10)
    b = -(10 ** 10)
    c = -(10 ** 10)
    if root.x < key:
        c = root.x
        b = prev(root.right, key)
    if b == -(10 ** 10) and c == -(10 ** 10):
        a = prev(root.left, key)
    return max(a, b, c)


def kth(root, k):
    if (get_size(root) < k):
        return 'none'
    if root == False:
        return 'none'
    if k - 1 == get_size(root.left):
        return root.x
    elif k - 1 < get_size(root.left):
        return kth(root.left, k)
    return kth(root.right, k - get_size(root.left) - 1)


def inputs():
    while True:
        try:
            line = input()
            yield line
        except (ValueError, EOFError):
            return


def main():
    root = False
    s = " "
    for s in inputs():
        if len(s) == 0:
            continue
        action, k = s.split()
        k = int(k)
        if action == 'insert':
            root = insert(root, k)
        elif action == 'delete':
            root = delete(root, k)
        elif action == 'exists':
            print(str(find(root, k)).lower())
        elif action == 'next':
            tmp = next(root, k)
            if tmp == 10 ** 10:
                print('none')
            else:
                print(tmp)
        elif action == 'prev':
            tmp = prev(root, k)
            if tmp == -(10 ** 10):
                print('none')
            else:
                print(tmp)
        else:
            print(kth(root, k))

if __name__ == '__main__':
    main()
