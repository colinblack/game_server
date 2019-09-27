package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ReplyAllianceRaceTakeGradeReward
	{
		public static const PROTO:String = "ProtoAlliance.ReplyAllianceRaceTakeGradeReward";
		public var package_root:*;
		public  var message:*;
		public var ret:int;
		public var uid:int;
		public var commons:CommonItemsCPP;
		public var userLevel:int;
		public var rankId:int;
		public var id:Vector.<int>;
		public function ReplyAllianceRaceTakeGradeReward(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ret = undefined;
			uid = undefined;
			commons = undefined;
			userLevel = undefined;
			rankId = undefined;
			id = new Vector.<int>();
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
			if(this.userLevel!= undefined)
			{
				serializeObj.userLevel = this.userLevel;
			}
			if(this.rankId!= undefined)
			{
				serializeObj.rankId = this.rankId;
			}
			serializeObj.id = [];
			for(var i:int = 0;i < this.id.length;i++)
			{
				serializeObj.id.push(this.id[i]);
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplyAllianceRaceTakeGradeReward
		{
			ret = undefined;
			uid = undefined;
			commons = undefined;
			userLevel = undefined;
			rankId = undefined;
			id = new Vector.<int>();
			this.ret = msgObj.ret;
			this.uid = msgObj.uid;
			if(msgObj.hasOwnProperty("commons"))
			{
				this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			}
			if(msgObj.hasOwnProperty("userLevel"))
			{
				this.userLevel = msgObj.userLevel;
			}
			if(msgObj.hasOwnProperty("rankId"))
			{
				this.rankId = msgObj.rankId;
			}
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
		public function decode(buffer:*):ReplyAllianceRaceTakeGradeReward
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}