package com.sanguo.game.server.connectlogic.common.message.ProtoOrder
{
	import laya.utils.Byte;
	public class OrderCPP
	{
		public static const PROTO:String = "ProtoOrder.OrderCPP";
		public var package_root:*;
		public  var message:*;
		public var slot:int;
		public var coin:int;
		public var exp:int;
		public var end_ts:int;
		public var needcost:Vector.<NeedCost>;
		public var discardcdtime:int;
		public var storageid:int;
		public var levelid:int;
		public var orderid:Byte;
		public function OrderCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			slot = undefined;
			coin = undefined;
			exp = undefined;
			end_ts = undefined;
			needcost = new Vector.<NeedCost>();
			discardcdtime = undefined;
			storageid = undefined;
			levelid = undefined;
			orderid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.slot = this.slot;
			serializeObj.coin = this.coin;
			serializeObj.exp = this.exp;
			serializeObj.end_ts = this.end_ts;
			serializeObj.needcost = [];
			for(var i:int = 0;i < this.needcost.length;i++)
			{
				serializeObj.needcost.push(this.needcost[i].serialize());
			}
			serializeObj.discardcdtime = this.discardcdtime;
			serializeObj.storageid = this.storageid;
			serializeObj.levelid = this.levelid;
			this.orderid.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):OrderCPP
		{
			slot = undefined;
			coin = undefined;
			exp = undefined;
			end_ts = undefined;
			needcost = new Vector.<NeedCost>();
			discardcdtime = undefined;
			storageid = undefined;
			levelid = undefined;
			orderid = undefined;
			this.slot = msgObj.slot;
			this.coin = msgObj.coin;
			this.exp = msgObj.exp;
			this.end_ts = msgObj.end_ts;
			for(var i:int = 0;i < msgObj.needcost.length;i++)
			{
				this.needcost.push(new NeedCost(package_root).unserialize(msgObj.needcost[i]));
			}
			this.discardcdtime = msgObj.discardcdtime;
			this.storageid = msgObj.storageid;
			this.levelid = msgObj.levelid;
			this.orderid = new Byte();
			this.orderid.writeArrayBuffer(msgObj.orderid);
			this.orderid.pos = 0;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):OrderCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}