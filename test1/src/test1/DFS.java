package test1;

import java.util.Stack;

public class DFS {
Stack stack=new Stack<Integer>();
int x;
int w;//v0的第一个邻接点
/**深度优先搜索--非递归式
* @param g ：图
* @param v0：开始节点
* @param vg：最终节点
*/
public void DF_Search(Graph g,int v0,int vg){
	stack.push(v0);//入栈
	g.mark[v0]=1;//v0被访问
	while(true){
		x=(Integer) stack.peek();//查看栈顶元素
		w=g.getFirstVex(x);
		while(g.mark[w]==1){//被访问，则寻找下一个邻接点
			w=g.getNextVex(x, w);
			if(w==-1){
			break;
			}
		}
		while(w==-1){//没有找到下一个邻接点
			stack.pop();
			x=(Integer) stack.peek();
			w=g.getFirstVex(x);
			while(g.mark[w]==1){
				w=g.getNextVex(x, w);
				if(w==-1){
					break;
				}
			}
		}
		stack.push(w);
		g.mark[w]=1;
		if(w==vg)
			break;//到达终点
		}
	new Count().show(g, stack);
	}
}