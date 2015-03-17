/*
Copyright (c) 2012-2015 The SSDB Authors. All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file.
*/
#ifndef SSDB_CLUSTER_H_
#define SSDB_CLUSTER_H_

#include "include.h"
#include <string>
#include <vector>

class KeyRange{
public:
	std::string begin;
	std::string end;
	KeyRange(){
	}
	KeyRange(const std::string &begin, const std::string &end){
		this->begin = begin;
		this->end = end;
	}
};

class Node{
public:
	const static int INIT    = 0;
	const static int SERVING = 1;
	
	int id;
	int status;
	std::string ip;
	int port;
	KeyRange range;
};

class SSDB;

class Cluster
{
public:
	static Cluster* create(SSDB *db);
	~Cluster();
	
	// 返回节点的 id
	int add_node(const std::string &ip, int port);
	int del_node(int id);
	int set_key_range(int id, const KeyRange &range);
	int get_node_list(std::vector<Node> *list);
	// 返回迁移的字节数
	int64_t migrate_data(int src_id, int dst_id, int keys);

private:
	SSDB *db;
	int next_id;
	std::vector<Node> node_list;
	
	Cluster();
};

#endif