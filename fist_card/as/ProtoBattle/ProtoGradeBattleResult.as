package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoGradeBattleResult
	{
		public static const PROTO:String = "ProtoBattle.ProtoGradeBattleResult";
		public var package_root:*;
		public  var message:*;
		public var grade:int;
		public var score:int;
		public var dailyScore:int;
		public function ProtoGradeBattleResult(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			grade = undefined;
			score = undefined;
			dailyScore = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.grade = this.grade;
			serializeObj.score = this.score;
			serializeObj.dailyScore = this.dailyScore;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoGradeBattleResult
		{
			grade = undefined;
			score = undefined;
			dailyScore = undefined;
			this.grade = msgObj.grade;
			this.score = msgObj.score;
			this.dailyScore = msgObj.dailyScore;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoGradeBattleResult
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}