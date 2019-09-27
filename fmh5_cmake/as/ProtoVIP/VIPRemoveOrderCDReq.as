package com.sanguo.game.server.connectlogic.common.message.ProtoVIP
{
	import laya.utils.Byte;
	public class VIPRemoveOrderCDReq
	{
		public static const PROTO:String = "ProtoVIP.VIPRemoveOrderCDReq";
		public var package_root:*;
		public  var message:*;
		public var orderud:int;
		public function VIPRemoveOrderCDReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			orderud = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.orderud = this.orderud;
			return serializeObj;
		}
		public function unserialize(msgObj:*):VIPRemoveOrderCDReq
		{
			orderud = undefined;
			this.orderud = msgObj.orderud;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):VIPRemoveOrderCDReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}