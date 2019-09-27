package com.sanguo.game.server.connectlogic.common.message.ProtoOrder
{
	import laya.utils.Byte;
	public class TruckQueryReq
	{
		public static const PROTO:String = "ProtoOrder.TruckQueryReq";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public function TruckQueryReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):TruckQueryReq
		{
			uid = undefined;
			this.uid = msgObj.uid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):TruckQueryReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}