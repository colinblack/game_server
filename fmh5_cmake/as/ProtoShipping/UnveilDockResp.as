package com.sanguo.game.server.connectlogic.common.message.ProtoShipping
{
	import laya.utils.Byte;
	public class UnveilDockResp
	{
		public static const PROTO:String = "ProtoShipping.UnveilDockResp";
		public var package_root:*;
		public  var message:*;
		public var shipping:ShippingCPP;
		public var shipboxes:Vector.<ShippingBoxCPP>;
		public function UnveilDockResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			shipping = undefined;
			shipboxes = new Vector.<ShippingBoxCPP>();
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
			return serializeObj;
		}
		public function unserialize(msgObj:*):UnveilDockResp
		{
			shipping = undefined;
			shipboxes = new Vector.<ShippingBoxCPP>();
			this.shipping = new ShippingCPP(package_root).unserialize(msgObj.shipping);
			for(var i:int = 0;i < msgObj.shipboxes.length;i++)
			{
				this.shipboxes.push(new ShippingBoxCPP(package_root).unserialize(msgObj.shipboxes[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):UnveilDockResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}