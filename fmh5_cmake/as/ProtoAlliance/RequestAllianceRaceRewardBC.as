package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestAllianceRaceRewardBC
	{
		public static const PROTO:String = "ProtoAlliance.RequestAllianceRaceRewardBC";
		public var package_root:*;
		public  var message:*;
		public var aid:int;
		public var uid:int;
		public var id:Vector.<int>;
		public function RequestAllianceRaceRewardBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			aid = undefined;
			uid = undefined;
			id = new Vector.<int>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.aid = this.aid;
			serializeObj.uid = this.uid;
			serializeObj.id = [];
			for(var i:int = 0;i < this.id.length;i++)
			{
				serializeObj.id.push(this.id[i]);
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestAllianceRaceRewardBC
		{
			aid = undefined;
			uid = undefined;
			id = new Vector.<int>();
			this.aid = msgObj.aid;
			this.uid = msgObj.uid;
			for(var i:int = 0;i < msgObj.id.length;i++)
			{
				this.id.push(msgObj.id[i]);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestAllianceRaceRewardBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}