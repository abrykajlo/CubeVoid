/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#pragma once

namespace cv {
template<class DataT>
struct Node
{
    DataT data;
    Node* next;

    Node();
    Node(DataT data);
    Node(DataT data, Node* next);
};

template<class DataT>
inline Node<DataT>::Node()
    : next(nullptr)
{}

template<class DataT>
inline Node<DataT>::Node(DataT data)
    : data(data)
    , next(nullptr)
{}

template<class DataT>
inline Node<DataT>::Node(DataT data, Node* next)
    : data(data)
    , next(next)
{}
}