package com.sanguo.game.server.connectlogic.common.message.ProtoShipping
{
	import laya.utils.Byte;
	public class PushShipBonusInfoMsg
	{
		public static const PROTO:String = "ProtoShipping.PushShipBonusInfoMsg";
		public var package_root:*;
		public  var message:*;
		public var vipshipbonus:ShipVIPBonusCPP;
		public function PushShipBonusInfoMsg(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			vipshipbonus = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.vipshipbonus = this.vipshipbonus.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):PushShipBonusInfoMsg
		{
			vipshipbonus = undefined;
			this.vipshipbonus = new ShipVIPBonusCPP(package_root).unserialize(msgObj.vipshipbonus);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PushShipBonusInfoMsg
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}