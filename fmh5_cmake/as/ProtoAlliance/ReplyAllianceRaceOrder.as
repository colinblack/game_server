package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ReplyAllianceRaceOrder
	{
		public static const PROTO:String = "ProtoAlliance.ReplyAllianceRaceOrder";
		public var package_root:*;
		public  var message:*;
		public var point:int;
		public var orderRecv:int;
		public var maxOrderRecv:int;
		public var flag:int;
		public var order:Vector.<AllianceRaceOrder>;
		public var memberOrder:Vector.<AllianceRaceMemberOrder>;
		public function ReplyAllianceRaceOrder(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			point = undefined;
			orderRecv = undefined;
			maxOrderRecv = undefined;
			flag = undefined;
			order = new Vector.<AllianceRaceOrder>();
			memberOrder = new Vector.<AllianceRaceMemberOrder>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.point = this.point;
			serializeObj.orderRecv = this.orderRecv;
			serializeObj.maxOrderRecv = this.maxOrderRecv;
			serializeObj.flag = this.flag;
			serializeObj.order = [];
			for(var i:int = 0;i < this.order.length;i++)
			{
				serializeObj.order.push(this.order[i].serialize());
			}
			serializeObj.memberOrder = [];
			for(var i:int = 0;i < this.memberOrder.length;i++)
			{
				serializeObj.memberOrder.push(this.memberOrder[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplyAllianceRaceOrder
		{
			point = undefined;
			orderRecv = undefined;
			maxOrderRecv = undefined;
			flag = undefined;
			order = new Vector.<AllianceRaceOrder>();
			memberOrder = new Vector.<AllianceRaceMemberOrder>();
			this.point = msgObj.point;
			this.orderRecv = msgObj.orderRecv;
			this.maxOrderRecv = msgObj.maxOrderRecv;
			this.flag = msgObj.flag;
			for(var i:int = 0;i < msgObj.order.length;i++)
			{
				this.order.push(new AllianceRaceOrder(package_root).unserialize(msgObj.order[i]));
			}
			for(var i:int = 0;i < msgObj.memberOrder.length;i++)
			{
				this.memberOrder.push(new AllianceRaceMemberOrder(package_root).unserialize(msgObj.memberOrder[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplyAllianceRaceOrder
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}