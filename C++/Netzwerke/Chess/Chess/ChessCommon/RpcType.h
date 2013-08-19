#pragma once

/*test:*/
//#define RPCTYPE_TO_STRING(x) case x: return #x; break;

/*anwendung:*/
//RPCTYPE_TO_STRING(RpcTypeLogin)

enum RpcType
{
	InvalidRpc = -1			,

	RpcTypeMove				,
	RpcTypeRequestBoard		,
	RpcTypeSendBoard		,
	RpcTypeLogin			,
	RpcTypeLoginResponse	,
	RpcTypeSuccess			,

	NumRpcTypes
};
