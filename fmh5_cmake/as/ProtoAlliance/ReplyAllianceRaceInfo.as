package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ReplyAllianceRaceInfo
	{
		public static const PROTO:String = "ProtoAlliance.ReplyAllianceRaceInfo";
		public var package_root:*;
		public  var message:*;
		public var point:int;
		public var raceLevel:int;
		public var overTs:int;
		public var flag:int;
		public var inRace:int;
		public var memberPoint:int;
		public var openRace:int;
		public function ReplyAllianceRaceInfo(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			point = undefined;
			raceLevel = undefined;
			overTs = undefined;
			flag = undefined;
			inRace = undefined;
			memberPoint = undefined;
			openRace = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.point = this.point;
			serializeObj.raceLevel = this.raceLevel;
			serializeObj.overTs = this.overTs;
			if(this.flag!= undefined)
			{
				serializeObj.flag = this.flag;
			}
			if(this.inRace!= undefined)
			{
				serializeObj.inRace = this.inRace;
			}
			if(this.memberPoint!= undefined)
			{
				serializeObj.memberPoint = this.memberPoint;
			}
			serializeObj.openRace = this.openRace;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplyAllianceRaceInfo
		{
			point = undefined;
			raceLevel = undefined;
			overTs = undefined;
			flag = undefined;
			inRace = undefined;
			memberPoint = undefined;
			openRace = undefined;
			this.point = msgObj.point;
			this.raceLevel = msgObj.raceLevel;
			this.overTs = msgObj.overTs;
			if(msgObj.hasOwnProperty("flag"))
			{
				this.flag = msgObj.flag;
			}
			if(msgObj.hasOwnProperty("inRace"))
			{
				this.inRace = msgObj.inRace;
			}
			if(msgObj.hasOwnProperty("memberPoint"))
			{
				this.memberPoint = msgObj.memberPoint;
			}
			this.openRace = msgObj.openRace;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplyAllianceRaceInfo
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}