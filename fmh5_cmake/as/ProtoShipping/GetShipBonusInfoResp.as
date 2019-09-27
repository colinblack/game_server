package com.sanguo.game.server.connectlogic.common.message.ProtoShipping
{
	import laya.utils.Byte;
	public class GetShipBonusInfoResp
	{
		public static const PROTO:String = "ProtoShipping.GetShipBonusInfoResp";
		public var package_root:*;
		public  var message:*;
		public var vipshipbonus:ShipVIPBonusCPP;
		public var point:FullBoxShipCPP;
		public function GetShipBonusInfoResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			vipshipbonus = undefined;
			point = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.vipshipbonus = this.vipshipbonus.serialize();
			if(this.point!= undefined)
			{
				serializeObj.point = this.point.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetShipBonusInfoResp
		{
			vipshipbonus = undefined;
			point = undefined;
			this.vipshipbonus = new ShipVIPBonusCPP(package_root).unserialize(msgObj.vipshipbonus);
			if(msgObj.hasOwnProperty("point"))
			{
				this.point = new FullBoxShipCPP(package_root).unserialize(msgObj.point);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetShipBonusInfoResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}