package com.sanguo.game.server.connectlogic.common.message.ProtoShipping
{
	import laya.utils.Byte;
	public class GetShipBonusInfoReq
	{
		public static const PROTO:String = "ProtoShipping.GetShipBonusInfoReq";
		public var package_root:*;
		public  var message:*;
		public function GetShipBonusInfoReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetShipBonusInfoReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetShipBonusInfoReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}