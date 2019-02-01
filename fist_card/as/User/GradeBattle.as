package com.sanguo.game.server.connectlogic.common.message.User
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class GradeBattle
	{
		public static const PROTO:String = "User.GradeBattle";
		public var package_root:*;
		public  var message:*;
		public var grade:int;
		public var dailyScore:int;
		public var score:int;
		public var ts:int;
		public function GradeBattle(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			grade = undefined;
			dailyScore = undefined;
			score = undefined;
			ts = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.grade = this.grade;
			serializeObj.dailyScore = this.dailyScore;
			serializeObj.score = this.score;
			serializeObj.ts = this.ts;
			return serializeObj;
		}
		public function unserialize(msgObj:*):GradeBattle
		{
			grade = undefined;
			dailyScore = undefined;
			score = undefined;
			ts = undefined;
			this.grade = msgObj.grade;
			this.dailyScore = msgObj.dailyScore;
			this.score = msgObj.score;
			this.ts = msgObj.ts;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GradeBattle
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}