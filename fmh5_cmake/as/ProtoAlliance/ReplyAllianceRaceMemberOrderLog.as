package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ReplyAllianceRaceMemberOrderLog
	{
		public static const PROTO:String = "ProtoAlliance.ReplyAllianceRaceMemberOrderLog";
		public var package_root:*;
		public  var message:*;
		public var member:Vector.<AllianceRaceMemberOrderLogItem>;
		public function ReplyAllianceRaceMemberOrderLog(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			member = new Vector.<AllianceRaceMemberOrderLogItem>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.member = [];
			for(var i:int = 0;i < this.member.length;i++)
			{
				serializeObj.member.push(this.member[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplyAllianceRaceMemberOrderLog
		{
			member = new Vector.<AllianceRaceMemberOrderLogItem>();
			for(var i:int = 0;i < msgObj.member.length;i++)
			{
				this.member.push(new AllianceRaceMemberOrderLogItem(package_root).unserialize(msgObj.member[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplyAllianceRaceMemberOrderLog
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}