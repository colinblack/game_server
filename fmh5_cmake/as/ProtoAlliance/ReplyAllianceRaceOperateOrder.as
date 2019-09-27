package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ReplyAllianceRaceOperateOrder
	{
		public static const PROTO:String = "ProtoAlliance.ReplyAllianceRaceOperateOrder";
		public var package_root:*;
		public  var message:*;
		public var ret:int;
		public var uid:int;
		public var operate:int;
		public var cdTs:int;
		public var commons:CommonItemsCPP;
		public var order:ReplyAllianceRaceOrder;
		public function ReplyAllianceRaceOperateOrder(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ret = undefined;
			uid = undefined;
			operate = undefined;
			cdTs = undefined;
			commons = undefined;
			order = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ret = this.ret;
			serializeObj.uid = this.uid;
			serializeObj.operate = this.operate;
			serializeObj.cdTs = this.cdTs;
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			if(this.order!= undefined)
			{
				serializeObj.order = this.order.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplyAllianceRaceOperateOrder
		{
			ret = undefined;
			uid = undefined;
			operate = undefined;
			cdTs = undefined;
			commons = undefined;
			order = undefined;
			this.ret = msgObj.ret;
			this.uid = msgObj.uid;
			this.operate = msgObj.operate;
			this.cdTs = msgObj.cdTs;
			if(msgObj.hasOwnProperty("commons"))
			{
				this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			}
			if(msgObj.hasOwnProperty("order"))
			{
				this.order = new ReplyAllianceRaceOrder(package_root).unserialize(msgObj.order);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplyAllianceRaceOperateOrder
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}