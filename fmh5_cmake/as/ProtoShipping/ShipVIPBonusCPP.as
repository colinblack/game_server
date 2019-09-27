package com.sanguo.game.server.connectlogic.common.message.ProtoShipping
{
	import laya.utils.Byte;
	public class ShipVIPBonusCPP
	{
		public static const PROTO:String = "ProtoShipping.ShipVIPBonusCPP";
		public var package_root:*;
		public  var message:*;
		public var remaincnt:int;
		public function ShipVIPBonusCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			remaincnt = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.remaincnt = this.remaincnt;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ShipVIPBonusCPP
		{
			remaincnt = undefined;
			this.remaincnt = msgObj.remaincnt;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ShipVIPBonusCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}