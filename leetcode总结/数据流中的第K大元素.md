



#### [703. 数据流中的第K大元素](https://leetcode-cn.com/problems/kth-largest-element-in-a-stream/)

设计一个找到数据流中第K大元素的类（class）。注意是排序后的第K大元素，不是第K个不同的元素。

你的 KthLargest 类需要一个同时接收整数 k 和整数数组nums 的构造器，它包含数据流中的初始元素。每次调用 KthLargest.add，返回当前数据流中第K大的元素。

示例:

int k = 3;
int[] arr = [4,5,8,2];
KthLargest kthLargest = new KthLargest(3, arr);
kthLargest.add(3);   // returns 4
kthLargest.add(5);   // returns 5
kthLargest.add(10);  // returns 5
kthLargest.add(9);   // returns 8
kthLargest.add(4);   // returns 8

#### 解题思路：

  利用优先级队列来实现。

优先级队列采用小根堆来实现，堆顶（队列首部）为最小元素。因此，定义一个包含k个元素的优先级队列，堆顶即为第k大元素。

插入时，如果队列大小小于k，则直接添加；否则，与堆顶对比，大于堆顶，则删除堆顶，插入新数据。

注意：在插入数据时，小根堆会自动调整堆结构，以满足结构特点。

代码如下：

```
class KthLargest {
    private PriorityQueue<Integer> queue;
    private int limit;
    public KthLargest(int k, int[] nums) {
        queue = new PriorityQueue<>(k);
        limit=k;
        for(int i:nums) {
            add(i);
        }
    }
    public int add(int val) {
        if(queue.size()<limit) {
            queue.add(val);
        } else if(val > queue.peek()) {
            queue.poll();
            queue.add(val);
        }
        return queue.peek();
    }
}
```

