package com.sanguo.game.server.connectlogic.common.message.User
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class User
	{
		public static const PROTO:String = "User.User";
		public var package_root:*;
		public  var message:*;
		public var base:Base;
		public var ts:int;
		public var activity:Activity;
		public var notifies:NotifyItemCPPAll;
		public var charges:AccumulateCharge;
		public var gameactivity:GameAcitivityAllCPP;
		public var item:Vector.<PropsItemCPP>;
		public var opents:int;
		public var heros:HerosInfo;
		public var cards:CardsInfo;
		public var unlock:UnlockCards;
		public var grade:GradeBattle;
		public var friends:FriendInfo;
		public var onhook:OnhookReward;
		public var allclub:MartialClub;
		public var post:PostItemCPPAll;
		public var drawRewardId:int;
		public var inviteInfo:Vector.<InivteUserInfoCPP>;
		public function User(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			base = undefined;
			ts = undefined;
			activity = undefined;
			notifies = undefined;
			charges = undefined;
			gameactivity = undefined;
			item = new Vector.<PropsItemCPP>();
			opents = undefined;
			heros = undefined;
			cards = undefined;
			unlock = undefined;
			grade = undefined;
			friends = undefined;
			onhook = undefined;
			allclub = undefined;
			post = undefined;
			drawRewardId = undefined;
			inviteInfo = new Vector.<InivteUserInfoCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.base = this.base.serialize();
			serializeObj.ts = this.ts;
			serializeObj.activity = this.activity.serialize();
			if(this.notifies!= undefined)
			{
				serializeObj.notifies = this.notifies.serialize();
			}
			serializeObj.charges = this.charges.serialize();
			serializeObj.gameactivity = this.gameactivity.serialize();
			serializeObj.item = [];
			for(var i:int = 0;i < this.item.length;i++)
			{
				serializeObj.item.push(this.item[i].serialize());
			}
			serializeObj.opents = this.opents;
			serializeObj.heros = this.heros.serialize();
			serializeObj.cards = this.cards.serialize();
			serializeObj.unlock = this.unlock.serialize();
			serializeObj.grade = this.grade.serialize();
			serializeObj.friends = this.friends.serialize();
			serializeObj.onhook = this.onhook.serialize();
			serializeObj.allclub = this.allclub.serialize();
			serializeObj.post = this.post.serialize();
			serializeObj.drawRewardId = this.drawRewardId;
			serializeObj.inviteInfo = [];
			for(var i:int = 0;i < this.inviteInfo.length;i++)
			{
				serializeObj.inviteInfo.push(this.inviteInfo[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):User
		{
			base = undefined;
			ts = undefined;
			activity = undefined;
			notifies = undefined;
			charges = undefined;
			gameactivity = undefined;
			item = new Vector.<PropsItemCPP>();
			opents = undefined;
			heros = undefined;
			cards = undefined;
			unlock = undefined;
			grade = undefined;
			friends = undefined;
			onhook = undefined;
			allclub = undefined;
			post = undefined;
			drawRewardId = undefined;
			inviteInfo = new Vector.<InivteUserInfoCPP>();
			this.base = new Base(package_root).unserialize(msgObj.base);
			this.ts = msgObj.ts;
			this.activity = new Activity(package_root).unserialize(msgObj.activity);
			if(msgObj.hasOwnProperty("notifies"))
			{
				this.notifies = new NotifyItemCPPAll(package_root).unserialize(msgObj.notifies);
			}
			this.charges = new AccumulateCharge(package_root).unserialize(msgObj.charges);
			this.gameactivity = new GameAcitivityAllCPP(package_root).unserialize(msgObj.gameactivity);
			for(var i:int = 0;i < msgObj.item.length;i++)
			{
				this.item.push(new PropsItemCPP(package_root).unserialize(msgObj.item[i]));
			}
			this.opents = msgObj.opents;
			this.heros = new HerosInfo(package_root).unserialize(msgObj.heros);
			this.cards = new CardsInfo(package_root).unserialize(msgObj.cards);
			this.unlock = new UnlockCards(package_root).unserialize(msgObj.unlock);
			this.grade = new GradeBattle(package_root).unserialize(msgObj.grade);
			this.friends = new FriendInfo(package_root).unserialize(msgObj.friends);
			this.onhook = new OnhookReward(package_root).unserialize(msgObj.onhook);
			this.allclub = new MartialClub(package_root).unserialize(msgObj.allclub);
			this.post = new PostItemCPPAll(package_root).unserialize(msgObj.post);
			this.drawRewardId = msgObj.drawRewardId;
			for(var i:int = 0;i < msgObj.inviteInfo.length;i++)
			{
				this.inviteInfo.push(new InivteUserInfoCPP(package_root).unserialize(msgObj.inviteInfo[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):User
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}