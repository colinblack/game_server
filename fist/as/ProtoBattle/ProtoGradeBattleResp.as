package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoGradeBattleResp
	{
		public static const PROTO:String = "ProtoBattle.ProtoGradeBattleResp";
		public var package_root:*;
		public  var message:*;
		public var grade:int;
		public var score:int;
		public var dailyScore:int;
		public var info:ProtoBattleDemo;
		public var commons:CommonItemsCPP;
		public function ProtoGradeBattleResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			grade = undefined;
			score = undefined;
			dailyScore = undefined;
			info = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.grade = this.grade;
			serializeObj.score = this.score;
			serializeObj.dailyScore = this.dailyScore;
			serializeObj.info = this.info.serialize();
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoGradeBattleResp
		{
			grade = undefined;
			score = undefined;
			dailyScore = undefined;
			info = undefined;
			commons = undefined;
			this.grade = msgObj.grade;
			this.score = msgObj.score;
			this.dailyScore = msgObj.dailyScore;
			this.info = new ProtoBattleDemo(package_root).unserialize(msgObj.info);
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoGradeBattleResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}