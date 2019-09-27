package com.sanguo.game.server.connectlogic.common.message.ProtoShipping
{
	import laya.utils.Byte;
	public class LeaveDockResp
	{
		public static const PROTO:String = "ProtoShipping.LeaveDockResp";
		public var package_root:*;
		public  var message:*;
		public var shipping:ShippingCPP;
		public var shipboxes:Vector.<ShippingBoxCPP>;
		public var commons:CommonItemsCPP;
		public var vipshipbonus:ShipVIPBonusCPP;
		public function LeaveDockResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			shipping = undefined;
			shipboxes = new Vector.<ShippingBoxCPP>();
			commons = undefined;
			vipshipbonus = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.shipping = this.shipping.serialize();
			serializeObj.shipboxes = [];
			for(var i:int = 0;i < this.shipboxes.length;i++)
			{
				serializeObj.shipboxes.push(this.shipboxes[i].serialize());
			}
			serializeObj.commons = this.commons.serialize();
			if(this.vipshipbonus!= undefined)
			{
				serializeObj.vipshipbonus = this.vipshipbonus.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):LeaveDockResp
		{
			shipping = undefined;
			shipboxes = new Vector.<ShippingBoxCPP>();
			commons = undefined;
			vipshipbonus = undefined;
			this.shipping = new ShippingCPP(package_root).unserialize(msgObj.shipping);
			for(var i:int = 0;i < msgObj.shipboxes.length;i++)
			{
				this.shipboxes.push(new ShippingBoxCPP(package_root).unserialize(msgObj.shipboxes[i]));
			}
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			if(msgObj.hasOwnProperty("vipshipbonus"))
			{
				this.vipshipbonus = new ShipVIPBonusCPP(package_root).unserialize(msgObj.vipshipbonus);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):LeaveDockResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}