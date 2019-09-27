package com.sanguo.game.server.connectlogic.common.message.ProtoNPCCustomer
{
	import laya.utils.Byte;
	public class GetNPCCustomerReq
	{
		public static const PROTO:String = "ProtoNPCCustomer.GetNPCCustomerReq";
		public var package_root:*;
		public  var message:*;
		public function GetNPCCustomerReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetNPCCustomerReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetNPCCustomerReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}