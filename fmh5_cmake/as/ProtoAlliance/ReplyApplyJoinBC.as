package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ReplyApplyJoinBC
	{
		public static const PROTO:String = "ProtoAlliance.ReplyApplyJoinBC";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var allianceId:int;
		public var ret:int;
		public var alliance:ApplyJoinResp;
		public function ReplyApplyJoinBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
			allianceId = undefined;
			ret = undefined;
			alliance = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			serializeObj.allianceId = this.allianceId;
			serializeObj.ret = this.ret;
			if(this.alliance!= undefined)
			{
				serializeObj.alliance = this.alliance.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplyApplyJoinBC
		{
			uid = undefined;
			allianceId = undefined;
			ret = undefined;
			alliance = undefined;
			this.uid = msgObj.uid;
			this.allianceId = msgObj.allianceId;
			this.ret = msgObj.ret;
			if(msgObj.hasOwnProperty("alliance"))
			{
				this.alliance = new ApplyJoinResp(package_root).unserialize(msgObj.alliance);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplyApplyJoinBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}