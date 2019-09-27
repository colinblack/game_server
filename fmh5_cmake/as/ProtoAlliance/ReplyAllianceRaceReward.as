package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ReplyAllianceRaceReward
	{
		public static const PROTO:String = "ProtoAlliance.ReplyAllianceRaceReward";
		public var package_root:*;
		public  var message:*;
		public var ret:int;
		public var uid:int;
		public var rankId:int;
		public var userLevel:int;
		public var olevel:int;
		public var opoint:int;
		public var gradeId:Vector.<int>;
		public var stageId:Vector.<int>;
		public function ReplyAllianceRaceReward(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ret = undefined;
			uid = undefined;
			rankId = undefined;
			userLevel = undefined;
			olevel = undefined;
			opoint = undefined;
			gradeId = new Vector.<int>();
			stageId = new Vector.<int>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ret = this.ret;
			serializeObj.uid = this.uid;
			serializeObj.rankId = this.rankId;
			serializeObj.userLevel = this.userLevel;
			serializeObj.olevel = this.olevel;
			serializeObj.opoint = this.opoint;
			serializeObj.gradeId = [];
			for(var i:int = 0;i < this.gradeId.length;i++)
			{
				serializeObj.gradeId.push(this.gradeId[i]);
			}
			serializeObj.stageId = [];
			for(var i:int = 0;i < this.stageId.length;i++)
			{
				serializeObj.stageId.push(this.stageId[i]);
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplyAllianceRaceReward
		{
			ret = undefined;
			uid = undefined;
			rankId = undefined;
			userLevel = undefined;
			olevel = undefined;
			opoint = undefined;
			gradeId = new Vector.<int>();
			stageId = new Vector.<int>();
			this.ret = msgObj.ret;
			this.uid = msgObj.uid;
			this.rankId = msgObj.rankId;
			this.userLevel = msgObj.userLevel;
			this.olevel = msgObj.olevel;
			this.opoint = msgObj.opoint;
			for(var i:int = 0;i < msgObj.gradeId.length;i++)
			{
				this.gradeId.push(msgObj.gradeId[i]);
			}
			for(var i:int = 0;i < msgObj.stageId.length;i++)
			{
				this.stageId.push(msgObj.stageId[i]);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplyAllianceRaceReward
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}