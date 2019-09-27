package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ReplyAllianceRaceBuyOrder
	{
		public static const PROTO:String = "ProtoAlliance.ReplyAllianceRaceBuyOrder";
		public var package_root:*;
		public  var message:*;
		public var ret:int;
		public var uid:int;
		public var commons:CommonItemsCPP;
		public function ReplyAllianceRaceBuyOrder(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ret = undefined;
			uid = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ret = this.ret;
			serializeObj.uid = this.uid;
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplyAllianceRaceBuyOrder
		{
			ret = undefined;
			uid = undefined;
			commons = undefined;
			this.ret = msgObj.ret;
			this.uid = msgObj.uid;
			if(msgObj.hasOwnProperty("commons"))
			{
				this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplyAllianceRaceBuyOrder
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}