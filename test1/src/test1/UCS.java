package test1;

import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

public class UCS {
	 
	public UCS(Graph g,int start,int end){
		int[] pre =new int[20];// 保存各个结点的前驱结点
		int[] dist =new int[20];// 用于保存当前结点到起始结点的实际路径长度
	for(int i =0; i < pre.length; i++){
		pre[i]=-1;
		dist[i]=10000;
	}
	// 调用一致搜索算法搜索路径
	UC_search(g,start, end, dist, pre);
	// 打印路径显示函数
	displayPath(start, end, pre,g);
	}
	/**
	* @param start：开始
	* @param goal：目的
	* @param prev：前驱节点
	* @param g：图
	*/
	public void displayPath(int start,int goal,int[] prev,Graph g){
		Stack<Integer> stack =new Stack<Integer>();
		stack.push(goal);
		while(prev[goal]!= start){
			stack.push(prev[goal]);
			goal = prev[goal];
		}
		stack.push(start);
		System.out.print("访问的下标: ");
		for(int i = stack.size()-1; i >=0; i--){
			System.out.print("-->"+stack.get(i));
		}
		System.out.print("\n访问过程: ");
		for(int i = stack.size()-1; i >=0; i--){
			System.out.print("-->"+ g.cities[stack.get(i)]);
		}
		System.out.print("\n总长度为： ");
		int result=0;
		for(int i =0; i < stack.size()-1; i++){
			result+=g.path[stack.get(i)][stack.get(i+1)];
		}
		System.out.print(result);
		System.out.println("\n");
		g.markInit();
	}
	/**
	* @param g：图
	* @param start：开始
	* @param goal：目的
	* @param prev：前驱节点
	*
	*/
	public void UC_search(Graph g,int start,int goal,int[] dist,int[] pre){
		List<Integer> list =new ArrayList<Integer>();
		list.add(start);
		while(!list.isEmpty()){
			moveMinToTop(list, dist);// 将dist数组中最小值所对应的结点，移至list队首
			int current = list.remove(0);// 将list队首的结点出队，并展开
			g.mark[current]=1;
			if(current == goal){
				return;
			}
			for(int j =0; j < g.path[current].length; j++){
				if(g.path[current][j]<10000&& g.mark[j]==0){
					if(!isInList(j, list)) {// 结点j不在队列里
						list.add(j);
						pre[j]= current;
						dist[j]= dist[current]+ g.path[current][j];
					}
					else if((dist[current]+ g.path[current][j])< dist[j]){
						pre[j]= current;
						dist[j]= dist[current]+ g.path[current][j];
					}
				}
			}
			if(list.isEmpty()){
				System.out.println("搜索不成功！");
			}
		}
	}
	/**
	* 检查结点a，是否在队列list里
	*/
	public boolean isInList(int a,List<Integer> list){
		for(int i =0; i < list.size(); i++){
			if(list.get(i)== a){
				return true;
			}
		}
		return false;
	}
	/**
	* 将dist数组中的最小值所对应的结点，从list队列中移至队列头
	*/
	public void moveMinToTop(List<Integer> list,int[] dist){
		int index =0;
		int min = dist[index];
		for(int i =0; i < list.size(); i++){
			int a = list.get(i);
			if(dist[a]< min){
				index = i;
				min = dist[a];
			}
		}
		int temp = list.get(index);
		for(int i = index; i >0; i--){
			list.set(i, list.get(i -1));
		}
		list.set(0, temp);
	}
}