package com.sanguo.game.server.connectlogic.common.message.ProtoShipping
{
	import laya.utils.Byte;
	public class PackBoxResp
	{
		public static const PROTO:String = "ProtoShipping.PackBoxResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public var boxes:ShippingBoxCPP;
		public var point:FullBoxShipCPP;
		public var viewAdPackCnt:int;
		public function PackBoxResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			commons = undefined;
			boxes = undefined;
			point = undefined;
			viewAdPackCnt = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			serializeObj.boxes = this.boxes.serialize();
			if(this.point!= undefined)
			{
				serializeObj.point = this.point.serialize();
			}
			if(this.viewAdPackCnt!= undefined)
			{
				serializeObj.viewAdPackCnt = this.viewAdPackCnt;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):PackBoxResp
		{
			commons = undefined;
			boxes = undefined;
			point = undefined;
			viewAdPackCnt = undefined;
			if(msgObj.hasOwnProperty("commons"))
			{
				this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			}
			this.boxes = new ShippingBoxCPP(package_root).unserialize(msgObj.boxes);
			if(msgObj.hasOwnProperty("point"))
			{
				this.point = new FullBoxShipCPP(package_root).unserialize(msgObj.point);
			}
			if(msgObj.hasOwnProperty("viewAdPackCnt"))
			{
				this.viewAdPackCnt = msgObj.viewAdPackCnt;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PackBoxResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}