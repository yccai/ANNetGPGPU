/// -*- tab-width: 8; Mode: C++; c-basic-offset: 8; indent-tabs-mode: t -*-
/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
   
   Author: Daniel Frenzel (dgdanielf@gmail.com)
*/

template <class Type>
Edge<Type>::Edge() {
	Type fValue = 0.f;
	Type fMomentum = 0.f;
	m_bAllowAdaptation = true;
}

template <class Type>
Edge<Type>::Edge(Edge<Type> *pEdge) {
	assert(pEdge);

	Type fValue = pEdge->GetValue();
	Type fMomentum = pEdge->GetMomentum();
	bool bAdapt = pEdge->GetAdaptationState();

	this->SetValue(fValue);
	this->SetMomentum(fMomentum);
	this->SetAdaptationState(bAdapt);

}

template <class Type>
Edge<Type>::Edge(AbsNeuron<Type> *first, AbsNeuron<Type> *second) {
	assert(first);
	assert(second);

	m_pNeuronFirst = first;
	m_pNeuronSecond = second;

	m_fWeight = GetRandReal(-0.5f, 0.5f);
	m_bAllowAdaptation = true;
	m_fMomentum = 0.f;
}

template <class Type>
Edge<Type>::Edge(AbsNeuron<Type> *first, AbsNeuron<Type> *second, Type fValue, Type fMomentum, bool bAdapt) {
	assert(first);
	assert(second);

	m_pNeuronFirst = first;
	m_pNeuronSecond = second;

	m_fWeight = fValue;
	m_bAllowAdaptation = bAdapt;
	m_fMomentum = fMomentum;
}

template <class Type>
AbsNeuron<Type> *Edge<Type>::GetDestination(AbsNeuron<Type> *source) const {
	assert(source);

	if(m_pNeuronFirst != source) {
		return m_pNeuronFirst;
	}
	else if(m_pNeuronSecond != source) {
		return m_pNeuronSecond;
	}
	else if(m_pNeuronFirst != source && m_pNeuronSecond != source) {
		std::cout<<"error: neuron does not belong to this chain"<<std::endl;
		return NULL;
	}
	else {
		std::cout<<"error: edge contains two identical neurons"<<std::endl;
		return NULL;
	}
}

template <class Type>
int Edge<Type>::GetDestinationID(AbsNeuron<Type> *pSource) const {
	return this->GetDestination(pSource)->GetID();
}

template <class Type>
const Type &Edge<Type>::GetValue() const {
	return m_fWeight;
}

template <class Type>
void Edge<Type>::SetValue(Type fValue) {
	m_fWeight = fValue;
}

template <class Type>
bool Edge<Type>::GetAdaptationState() const {
	return m_bAllowAdaptation;
}

template <class Type>
void Edge<Type>::SetAdaptationState(const bool &adapt)	{
	m_bAllowAdaptation = adapt;
}

template <class Type>
const Type &Edge<Type>::GetMomentum() const {
	return m_fMomentum;
}

template <class Type>
void Edge<Type>::SetMomentum(Type fValue) {
	m_fMomentum = fValue;
}

template <class Type>
Edge<Type>::operator Type() const {
	return this->GetValue();
}


