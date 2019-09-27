package com.sanguo.game.server.connectlogic.common.message.ProtoNPCCustomer
{
	import laya.utils.Byte;
	public class RefuseSellPropsReq
	{
		public static const PROTO:String = "ProtoNPCCustomer.RefuseSellPropsReq";
		public var package_root:*;
		public  var message:*;
		public var propsId:int;
		public function RefuseSellPropsReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			propsId = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.propsId = this.propsId;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RefuseSellPropsReq
		{
			propsId = undefined;
			this.propsId = msgObj.propsId;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RefuseSellPropsReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}