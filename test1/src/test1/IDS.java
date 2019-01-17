package test1;

import java.util.Stack;

public class IDS {
	Stack stack=new Stack<Integer>();
	/**迭代加深搜索
	* @param g：图
	* @param v0：开始节点
	* @param vg：目的节点
	* @param depthMax：depthMax
	*/
	public void IDS_Search(Graph g,int v0,int vg,int depthMax){
		for(int i =2; i <=depthMax; i++){//迭代depthMax次
			if(dfsearch(g, v0, vg,i)==1){
				break;
			}
		}
	}
	/**深度搜索
	* @param g：图
	* @param v0：开始节点
	* @param vg：目的节点
	* @param depthMax：depthMax
	* @return
	*/
	public int dfsearch(Graph g,int v0,int vg,int depthMax){
	int x;
	int w;//v0的第一个邻接点
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
			if(stack.size()==0){//清空了栈里的元素
				g.markInit();//访问初始化
				return 0;
			}
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
		if(w==vg){
			break;
		}//检查是否达到终点
		if(stack.size()>=depthMax){//重新迭代则重新初始化值
			stack.pop();
		}
	}
	new Count().show(g, stack);
	return 1;
	}
}